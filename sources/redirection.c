/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:04:59 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/16 21:23:21 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in(t_minishell *minishell, t_token *current)
{
	minishell->input_fd = open(current->next->value, O_RDONLY);
	if (minishell->input_fd < 0)
	{
		perror(current->next->value);
		minishell->error_code = -1;
		return (-1);
	}
	minishell->saved_inputfd = dup(STDIN_FILENO);
	if (dup2(minishell->input_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(minishell->input_fd);
		minishell->error_code = -1;
		return (-1);
	}
	close(minishell->input_fd);
	return (0);
}

int	redir_out(t_minishell *minishell, t_token *current)
{
	minishell->output_fd = open(current->next->value,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (minishell->output_fd < 0)
	{
		perror(current->next->value);
		minishell->error_code = -1;
		return (-1);
	}
	minishell->saved_outputfd = dup(STDOUT_FILENO);
	if (dup2(minishell->output_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(minishell->output_fd);
		minishell->error_code = -1;
		return (-1);
	}
	close(minishell->output_fd);
	return (0);
}
int	redir_append(t_minishell *minishell, t_token *current)
{
	minishell->output_fd = open(current->next->value,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (minishell->output_fd < 0)
	{
		perror(current->next->value);
		minishell->error_code = -1;
		return (-1);
	}
	minishell->saved_outputfd = dup(STDOUT_FILENO);
	if (dup2(minishell->output_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(minishell->output_fd);
		return (-1);
	}
	close(minishell->output_fd);
	return (0);
}
 int redir_heredoc(t_minishell *minishell, t_token *current)
 {
	create_heredoc(current->next->value, minishell);
	if (minishell->input_fd < 0)
		return (-1);
	minishell->saved_inputfd = dup(STDIN_FILENO);
	if (dup2(minishell->input_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(minishell->input_fd);
		return (-1);
	}
	close(minishell->input_fd);
	return(0);
 }
