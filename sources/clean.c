/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:46 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/13 16:49:10 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free_tab(current->args);
		// free(current->type);
		free(current);
		current = next;
	}
	*cmds = NULL;
}

static void	free_envp(t_envp **envp)
{
	t_envp	*current;
	t_envp	*next;

	if (!envp || !*envp)
		return ;
	current = *envp;
	while (current)
	{
		next = current->next;
		free(current->value);
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
	free_minishell(minishell);
	exit(minishell->error_code);
}

void	free_minishell(t_minishell *minishell)
{
	// int line;
	// line = 0;
	printf("curren");
	if (!minishell)
		return ;
	if (minishell->envp)
		free_envp(&minishell->envp);
	if (minishell->tokens)
		free_tokens(&minishell->tokens);
	printf("%p",minishell->cmds);
	if (minishell->cmds)
	{
		printf("currefdfddsfdsfdn");
		free_cmds(&minishell->cmds);
	}
	rl_clear_history();
	if (minishell->input_fd > 2)
		close(minishell->input_fd);
}
