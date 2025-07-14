/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:05 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/14 15:25:14 by tsaby            ###   ########.fr       */
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

int	handle_heredoc_input(int fd, char *limiter)
{
	char	*line;
	int		interrupted;

	interrupted = 0;
	rl_event_hook = stop_readline;
	signal(SIGINT, heredoc_signal_handler);
	while (1)
	{
		if (g_signal_value == 1)
		{
			interrupted = -2;
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

int	handle_heredoc(int fd, char *limiter, char *tmp_filename)
{
	int	ret;

	ret = 0;
	ret = handle_heredoc_input(fd, limiter);
	if (ret < 0)
	{
		unlink(tmp_filename);
		free(tmp_filename);
		return (ret);
	}
	return (ret);
}

static int	create_heredoc(char *limiter, t_minishell *minishell,
		t_token *redir)
{
	char	*tmp_filename;
	int		ret;

	ret = 0;
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
	ret = handle_heredoc(minishell->h_fd, limiter, tmp_filename);
	if (ret < 0)
		return (ret);
	free(redir->next->value);
	redir->next->value = tmp_filename;
	if (create_list_heredoc(tmp_filename, minishell) < 0)
		return (-1);
	return (0);
}

int	prepare_heredocs(t_minishell *minishell, t_cmds *cmds)
{
	t_token	*token;
	int		ret;

	while (cmds)
	{
		token = cmds->redirs;
		while (token)
		{
			if (token->type == T_HEREDOC)
			{
				ret = create_heredoc(token->next->value, minishell, token);
				if (ret < 0)
				{
					if (ret == -1)
						perror("heredoc");
					cleanup_heredocs(minishell);
					return (ret);
				}
			}
			token = token->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
