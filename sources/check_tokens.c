/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:00:24 by egache            #+#    #+#             */
/*   Updated: 2025/06/19 16:12:08 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_operators(t_token *tokens, t_minishell *minishell)
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

static char	*check_pipes(t_token *tokens)
{
	if (tokens->next == NULL)
		return (E_PARS_PIPE);
	else
		return (NULL);
	return (NULL);
}

char	*check_syntax(t_minishell *minishell)
{
	t_token	*current;
	char	*syntax_error;

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

bool	check_cmd(t_minishell *minishell, char *arg)
{
	struct stat	fs;

	if (ft_strncmp("./", arg, 2) == 0 || ft_strncmp("/", arg, 1) == 0)
	{
		if (stat(arg, &fs) == 0 && !S_ISREG(fs.st_mode))
		{
			ft_printf_fd(2, E_IS_DIR, arg);
			minishell->error_code = 126;
			return (false);
		}
		if (is_valid_cmd(arg, minishell) == true)
			return (true);
		if (ft_strnstr(arg, "/", ft_strlen(arg)) != NULL)
		{
			access(arg, X_OK);
			if (errno == 13)
				ft_printf_fd(2, E_NO_PERM, arg);
			else if (errno == 2)
				ft_printf_fd(2, E_NSFOD, arg);
			else if (errno == 0)
				return (true);
			minishell->error_code = 127;
			return (false);
		}
	}
	else
	{
		if (arg[0] != '\0')
		{
			if (is_valid_cmd(arg, minishell) == true)
				return (true);
			ft_printf_fd(2, E_PARS_CMD_NF, arg);
			minishell->error_code = 127;
			return (false);
		}
	}
	return (false);
}

bool	check_tokens(t_minishell *minishell)
{
	char	*syntax_error;

	syntax_error = check_syntax(minishell);
	if (syntax_error != NULL)
	{
		minishell->error_code = 2;
		clean_error(syntax_error, minishell);
		return (false);
	}
	return (true);
}
