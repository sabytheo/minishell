/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:46 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/01 20:24:39 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit_pipes(t_minishell *minishell)
{
	if (minishell->pipes)
		cleanup_pipes(minishell->pipes, minishell->cmds_count - 1);
	if (minishell->pids)
		free(minishell->pids);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_running_minishell(t_minishell *minishell)
{
	if (ft_strlen(minishell->entry) > 0)
	{
		if (minishell->cmds->args && minishell->cmds->args[0]
			&& !minishell->cmds->next)
		{
			free(minishell->path);
			minishell->path = NULL;
		}
		free_cmds(&minishell->cmds);
		free_heredoc(&minishell->heredoc);
		free_tokens(&minishell->tokens);
	}
	free(minishell->entry);
	minishell->cmds_count = 0;
	minishell->errfound = false;
}

void	free_minishell(t_minishell *minishell, char *error_message,
		bool exit_needed)
{
	if (minishell->entry)
		free(minishell->entry);
	if (minishell->envp)
		free_denvp(&minishell->envp);
	if (minishell->envp_tab)
		free_tab(minishell->envp_tab);
	if (minishell->export)
		free_denvp(&minishell->export);
	if (minishell->tokens)
		free_tokens(&minishell->tokens);
	if (minishell->heredoc)
		free_heredoc(&minishell->heredoc);
	if (minishell->cmds)
		free_cmds(&minishell->cmds);
	if (minishell->cmds_count != 0)
		free_exit_pipes(minishell);
	rl_clear_history();
	if (minishell->input_fd > 2)
		close(minishell->input_fd);
	if (minishell->output_fd > 2)
		close(minishell->output_fd);
	if (error_message != NULL)
		ft_printf_fd(2, "%s\n", error_message);
	if (exit_needed == true)
		exit(EXIT_FAILURE);
}
