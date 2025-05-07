/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:00:24 by egache            #+#    #+#             */
/*   Updated: 2025/05/07 17:23:45 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_syntax(t_minishell *minishell)
{
	t_token	*current;
	bool	syntax_error;

	current = minishell->tokens;
	syntax_error = false;
	chainedlst_to_tab(minishell, minishell->envp);
	if (current->type == T_PIPE)
		return (true);
	while (current != NULL && syntax_error == false)
	{
		if (current->type == T_REDIR_IN || current->type == T_REDIR_OUT
			|| current->type == T_APPEND || current->type == T_HEREDOC)
		{
			syntax_error = check_operators(current);
		}
		else if (current->type == T_PIPE)
			syntax_error = check_pipes(current);
		current = current->next;

	}
}

bool	check_operators(t_token *tokens)
{
	if (tokens->next == NULL)
		return (true);
	else if (tokens->next != NULL)
	{
		if (tokens->next->type == T_REDIR_IN
			|| tokens->next->type == T_REDIR_OUT
			|| tokens->next->type == T_APPEND
			|| tokens->next->type == T_HEREDOC)
			return (true);
		
		else
			return (false);
	}
}
bool check_pipes(t_token *tokens)
{
	if (tokens->next == NULL)
		return (true);
	if (tokens->next != NULL && tokens->next->type != T_WORD)
	{
		if (tokens->next->next == NULL)
			return (true);
		else
			return (false);
	}
}
