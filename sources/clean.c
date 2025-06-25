/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:46 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/25 16:30:02 by egache           ###   ########.fr       */
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
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	cleanup_pipes(minishell->pipes, minishell->cmds_count - 1);
	free(minishell->pids);
	minishell->pids = NULL;
}

void	free_exit_pipes(t_minishell *minishell)
{
	if (minishell->pipes)
		cleanup_pipes(minishell->pipes, minishell->cmds_count - 1);
	if (minishell->pids)
		free(minishell->pids);
}

int	exit_and_clear_child(int error_code, t_minishell *minishell)
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

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*current;
	t_cmds	*next;

	if (!cmds || !*cmds)
		return ;
	current = *cmds;
	while (current)
	{
		next = current->next;
		free_tokens(&current->redirs);
		free_tab(current->args);
		free(current);
		current = next;
	}
	*cmds = NULL;
}

void	free_heredoc(t_heredoc **heredoc)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (!heredoc || !*heredoc)
		return ;
	current = *heredoc;
	while (current)
	{
		next = current->next;
		// free(current->filename);
		free(current);
		current = next;
	}
	*heredoc = NULL;
}

void	free_denvp(t_denvp **envp)
{
	t_denvp	*current;
	t_denvp	*next;

	if (!envp || !*envp)
		return ;
	current = *envp;
	while (current)
	{
		next = current->next;
		free_tab(current->var);
		free(current);
		current = next;
	}
	*envp = NULL;
}

/*
** Clean and exit function.
** Print error message,clean then exit.
*/
void	clean_error(char *error_message, t_minishell *minishell)
{
	// besoin de completer cette fonction pour tout bien clean,free.
	if (error_message)
		ft_printf_fd(2, error_message, minishell->error_item);
	// free_minishell(minishell);
	// exit(minishell->error_code);
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

void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
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
}
