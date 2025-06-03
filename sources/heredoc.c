/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:05 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/03 18:18:04 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_TMP ".heredoc_tmp"

int	create_heredoc(char *eof, t_minishell *minishell)
{
	char	*line;
	size_t	len;

	len = ft_strlen(eof);
	minishell->heredoc_fd = open(HEREDOC_TMP, O_CREAT | O_WRONLY | O_TRUNC,
			0600);
	if (minishell->heredoc_fd < 0)
		return (perror("open heredoc"), -1);
	while (1)
	{
		ft_printf("minishell_heredoc>");
		if( minishell->saved_inputfd > 2)
			reset_redir(minishell);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			printf("test\n");
			break ;
		}
		if (strncmp(line, eof, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		// ft_printf_fd(minishell->heredoc_fd,"%s",line);
		write(minishell->heredoc_fd, line, ft_strlen(line));
		free(line);
	}
	close(minishell->heredoc_fd);
	minishell->input_fd = open(HEREDOC_TMP, O_RDONLY);
	if (minishell->input_fd < 0)
	{
		perror("open heredoc");
		unlink(HEREDOC_TMP);
		return (-1);
	}
	unlink(HEREDOC_TMP);
	return (0);
}
