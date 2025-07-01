/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:10:12 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/01 14:26:52 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_minishell *minishell)
{
	if (minishell->saved_inputfd >= 0)
	{
		close(minishell->saved_inputfd);
		minishell->saved_inputfd = -1;
	}
	if (minishell->saved_outputfd >= 0)
	{
		close(minishell->saved_outputfd);
		minishell->saved_outputfd = -1;
	}
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);
	cleanup_pipes(minishell->pipes, minishell->cmds_count - 1);
	free(minishell->pids);
	minishell->pids = NULL;
}

int	exit_and_clear_child_pipe(int error_code, t_minishell *minishell)
{
	if (!minishell->cmds->next)
		free(minishell->path);
	if (minishell->tokens)
		free_tokens(&minishell->tokens);
	if (minishell->cmds)
		free_cmds(&minishell->cmds);
	if (minishell->entry)
		free(minishell->entry);
	if (minishell->export)
		free_denvp(&minishell->export);
	if (minishell->envp)
		free_denvp(&minishell->envp);
	if (minishell->envp_tab)
		free_tab(minishell->envp_tab);
	if (minishell->heredoc)
		free_heredoc(&minishell->heredoc);
	close_fds(minishell);
	exit(error_code);
}

int	exit_and_clear_child(int error_code, t_minishell *minishell)
{
	if (!minishell->cmds->next)
		free(minishell->path);
	if (minishell->tokens)
		free_tokens(&minishell->tokens);
	if (minishell->cmds)
		free_cmds_child(&minishell->cmds);
	if (minishell->entry)
		free(minishell->entry);
	if (minishell->export)
		free_denvp(&minishell->export);
	if (minishell->envp)
		free_denvp(&minishell->envp);
	if (minishell->envp_tab)
		free_tab(minishell->envp_tab);
	if (minishell->heredoc)
		free_heredoc(&minishell->heredoc);
	close_fds(minishell);
	exit(error_code);
}
