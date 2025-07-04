/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:05 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/04 15:06:45 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_line(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

static int	handle_heredoc_input(int fd, char *limiter)
{
	char	*line;
	int	interrupted;

	interrupted = 0;
	rl_event_hook = stop_readline;
	signal(SIGINT, heredoc_signal_handler);
	while (1)
	{
		if (g_signal_value == 1)
		{
			interrupted = -1;
			break ;
		}
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, fd);
	}
	rl_event_hook = NULL;
	signal(SIGINT, signal_handler);
	close(fd);
	return (interrupted);
}

static char	*generate_tmp_filename(void)
{
	static int	heredoc_id = 1;
	char		*id;
	char		*tmp;

	id = ft_itoa(heredoc_id++);
	if (!id)
		return (NULL);
	tmp = ft_strjoin(".heredoc_tmp_", id);
	free(id);
	return (tmp);
}

static int	create_heredoc(char *limiter, t_minishell *minishell,
		t_token *redir)
{
	char	*tmp_filename;

	tmp_filename = generate_tmp_filename();
	if (!tmp_filename)
		return (-1);
	minishell->h_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (minishell->h_fd < 0)
	{
		free(tmp_filename);
		minishell->input_fd = -1;
		return (-1);
	}
	if (handle_heredoc_input(minishell->h_fd, limiter) < 0)
	{
		unlink(tmp_filename);
		if (ft_strcmp(tmp_filename, ".heredoc_tmp_1") == 0)
			close(minishell->h_fd);
		free(tmp_filename);
		return (-1);
	}
	free(redir->next->value);
	redir->next->value = tmp_filename;
	if (create_list_heredoc(tmp_filename, minishell) < 0)
		return (-1);
	return (0);
}

int	prepare_heredocs(t_minishell *minishell, t_cmds *cmds)
{
	t_cmds	*current;
	t_token	*token;

	current = cmds;
	while (current)
	{
		token = current->redirs;
		while (token)
		{
			if (token->type == T_HEREDOC)
			{
				if (create_heredoc(token->next->value, minishell, token) < 0)
				{
					perror("heredoc");
					return (-1);
				}
			}
			token = token->next;
		}
		current = current->next;
	}
	return (0);
}
