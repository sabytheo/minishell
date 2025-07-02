/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:04:59 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/02 17:23:05 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in(t_minishell *minishell, t_token *current, bool cmdfound)
{
	minishell->input_fd = open(current->next->value, O_RDONLY);
	if (minishell->input_fd < 0)
	{
		perror(current->next->value);
		minishell->error_code = 1;
		return (-1);
	}
	if (cmdfound == true)
	{
		if (minishell->saved_inputfd == -1)
			minishell->saved_inputfd = dup(STDIN_FILENO);
		if (dup2(minishell->input_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->input_fd);
			minishell->error_code = 1;
			return (-1);
		}
	}
	close(minishell->input_fd);
	return (0);
}

int	redir_out(t_minishell *minishell, t_token *current, bool cmdfound)
{
	minishell->output_fd = open(current->next->value,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (minishell->output_fd < 0)
	{
		perror(current->next->value);
		minishell->error_code = 1;
		return (-1);
	}
	if (cmdfound == true)
	{
		if (minishell->saved_outputfd == -1)
			minishell->saved_outputfd = dup(STDOUT_FILENO);
		if (dup2(minishell->output_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->output_fd);
			minishell->error_code = 1;
			return (-1);
		}
	}
	close(minishell->output_fd);
	return (0);
}

int	redir_append(t_minishell *minishell, t_token *current, bool cmdfound)
{
	minishell->output_fd = open(current->next->value,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (minishell->output_fd < 0)
	{
		perror(current->next->value);
		minishell->error_code = 1;
		return (-1);
	}
	if (cmdfound == true)
	{
		if (minishell->saved_outputfd == -1)
			minishell->saved_outputfd = dup(STDOUT_FILENO);
		if (dup2(minishell->output_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->output_fd);
			return (-1);
		}
	}
	close(minishell->output_fd);
	return (0);
}

void	reset_redir(t_minishell *minishell)
{
	if (minishell->saved_inputfd > 2)
	{
		if (dup2(minishell->saved_inputfd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->saved_inputfd);
		}
		close(minishell->saved_inputfd);
		minishell->saved_inputfd = -1;
	}
	if (minishell->saved_outputfd > 2)
	{
		if (dup2(minishell->saved_outputfd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->saved_outputfd);
		}
		close(minishell->saved_outputfd);
		minishell->saved_outputfd = -1;
	}
}

int	setup_redirections(t_token *current, t_minishell *minishell, bool cmdfound)
{
	int	errfound;

	errfound = 0;
	while (current)
	{
		if (current->type == T_REDIR_IN || current->type == T_HEREDOC)
			errfound = redir_in(minishell, current, cmdfound);
		else if (current->type == T_REDIR_OUT)
			errfound = redir_out(minishell, current, cmdfound);
		else if (current->type == T_APPEND)
			errfound = redir_append(minishell, current, cmdfound);
		if (errfound < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
