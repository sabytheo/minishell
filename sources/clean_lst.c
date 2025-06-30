/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:06:07 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/30 10:07:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
