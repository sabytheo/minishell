/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:05 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/11 19:28:38 by tsaby            ###   ########.fr       */
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
				create_heredoc(token->next->value, minishell);
				if (minishell->input_fd < 0)
				{
					perror("heredoc");
					return (-1);
				}
				close(minishell->input_fd);
			}
			token = token->next;
		}
		current = current->next;
	}
	return (0);
}

void	create_heredoc(char *limiter, t_minishell *minishell)
{
	static int	heredoc_id = 1;
	char		*id;
	char		*tmp_filename;
	char		*tmp;
	char		*line;

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
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(minishell->heredoc_fd, line, ft_strlen(line));
		write(minishell->heredoc_fd, "\n", 1);
		free(line);
	}
	close(minishell->heredoc_fd);
	t_heredoc	*new;
	new = create_heredoc_node(tmp_filename);
	if (!new)
	{
		perror("malloc_heredoc");
		free(tmp_filename);
		return ;
	}
	add_heredoc_back(&minishell->heredoc, new);
	minishell->input_fd = open(tmp_filename, O_RDONLY);
}
