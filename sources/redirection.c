/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:04:59 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/19 14:44:33 by egache           ###   ########.fr       */
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

// static char	*get_filename(t_minishell *minishell)
// {
// 	t_heredoc	*current;
// 	char		*filename;

// 	current = minishell->heredoc;
// 	if (!current)
// 		return (NULL);
// 	filename = current->filename;
// 	minishell->heredoc = current->next;
// 	free(current);
// 	return (filename);
// }
// int	redir_heredoc(t_minishell *minishell, bool cmdfound)
// {
// 	char	*filename;

// 	filename = get_filename(minishell);
// 	if (!filename)
// 	{
// 		perror("filename missing");
// 		return (-1);
// 	}
// 	minishell->input_fd = open(filename, O_RDONLY);
// 	if (minishell->input_fd < 0)
// 		return (-1);
// 	if (minishell->saved_inputfd == -1)
// 		minishell->saved_inputfd = dup(STDIN_FILENO);
// 	if (cmdfound == true)
// 	{
// 		if (dup2(minishell->input_fd, STDIN_FILENO) < 0)
// 		{
// 			perror("dup2");
// 			close(minishell->input_fd);
// 			return (-1);
// 		}
// 	}
// 	close(minishell->input_fd);
// 	unlink(filename);
// 	return (0);
// }
