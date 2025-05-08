/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:00:24 by egache            #+#    #+#             */
/*   Updated: 2025/05/08 15:04:38 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *check_operators(t_token *tokens, t_minishell *minishell)
{
	if (tokens->next == NULL)
		return (E_PARS_OPE_E);
	else if (tokens->next != NULL && tokens->next->type == T_PIPE)
		return (E_PARS_PIPE);
	else if (tokens->next != NULL)
	{
		if (tokens->next->type >= T_REDIR_IN && tokens->next->type <= T_HEREDOC)
		{
			minishell->error_item = tokens->next->value;
			return (E_PARS_OPE_D);
		}
		else
			return (NULL);
	}
	return (NULL);
}

static char *check_pipes(t_token *tokens)
{
	if (tokens->next == NULL)
		return (E_PARS_PIPE);
	else
		return (NULL);
	return (NULL);
}

char *check_syntax(t_minishell *minishell)
{
	t_token *current;
	char *syntax_error;

	current = minishell->tokens;
	if (current->type == T_PIPE)
		return (syntax_error = E_PARS_PIPE);
	while (current != NULL)
	{
		if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			syntax_error = check_operators(current, minishell);
			if (syntax_error != NULL)
				return (syntax_error);
		}
		else if (current->type == T_PIPE)
		{
			syntax_error = check_pipes(current);
			if (syntax_error != NULL)
				return (syntax_error);
		}
		current = current->next;
	}
	return (NULL);
}

int check_cmd(t_minishell *minishell)
{
	t_token *current;
	bool errfound;

	current = minishell->tokens;
	chainedlst_to_tab(minishell, minishell->envp);
	errfound = false;
	while (current != NULL)
	{
		if (current->type == T_WORD)
		{
			if (is_valid_cmd(current->value, minishell) == false && errfound == false)
			{
				minishell->error_code = 127;
				errfound = true;
				ft_printf_fd(2, E_PARS_CMD_NF, current->value);
			}
		}
		if (current->type == T_PIPE)
			errfound = false;
		current = current->next;
	}
	return (0);
}

void check_tokens(t_minishell *minishell)
{
	char *syntax_error;

	syntax_error = check_syntax(minishell);
	if (syntax_error != NULL)
	{
		minishell->error_code = 2;
		clean_error(syntax_error, minishell);
	}
	check_cmd(minishell);
	return;
}