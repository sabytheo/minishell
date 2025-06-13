/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:05 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/13 09:54:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	handle_heredoc_input(int fd, char *limiter, t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		line = expand_variable(line, minishell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

int	create_list(char *filename, t_minishell *minishell)
{
	t_heredoc	*new;

	new = create_heredoc_node(filename);
	if (!new)
	{
		perror("malloc_heredoc");
		free(filename);
		return (-1);
	}
	add_heredoc_back(&minishell->heredoc, new);
	return (0);
}

int	create_heredoc(char *limiter, t_minishell *minishell, t_token *redir)
{
	static int	heredoc_id = 1;
	char		*id;
	char		*tmp_filename;
	char		*tmp;

	id = ft_itoa(heredoc_id++);
	tmp = ft_strjoin(".heredoc_tmp_", id);
	tmp_filename = tmp;
	free(id);
	minishell->heredoc_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC,
			0600);
	if (minishell->heredoc_fd < 0)
	{
		perror("open heredoc_fd");
		free(tmp_filename);
		minishell->input_fd = -1;
		return (-1);
	}
	handle_heredoc_input(minishell->heredoc_fd, limiter, minishell);
	free(redir->next->value);
	redir->next->value = tmp_filename;
	if (create_list(tmp_filename, minishell) < 0)
		return (-1);
	return (0);
}
