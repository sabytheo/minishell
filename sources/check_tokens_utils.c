/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:27:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/06 18:25:55 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_a_builtins(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "cd", len) == 0 && len == 2)
		return (true);
	if (ft_strncmp(cmd, "echo", len) == 0 && len == 4)
		return (true);
	if (ft_strncmp(cmd, "env", len) == 0 && len == 3)
		return (true);
	if (ft_strncmp(cmd, "exit", len) == 0 && len == 4)
		return (true);
	if (ft_strncmp(cmd, "export", len) == 0 && len == 6)
		return (true);
	if (ft_strncmp(cmd, "pwd", len) == 0 && len == 3)
		return (true);
	if (ft_strncmp(cmd, "unset", len) == 0 && len == 5)
		return (true);
	return (false);
}

bool	is_valid_cmd(char *cmd, t_minishell *minishell)
{
	char	*path;

	if (is_a_builtins(cmd))
		return (true);
	path = find_path(cmd, minishell->envp_tab, 0);
	if (path != NULL)
	{
		free(path);
		return (true);
	}
	free(path);
	return (false);
}

bool	check_first_token(t_minishell *minishell, t_token **current)
{
	bool	ret;

	ret = false;
	if (is_valid_cmd((*current)->value, minishell) == false
		&& (*current)->type == T_WORD)
	{
		ft_printf_fd(2, E_PARS_CMD_NF, (*current)->value);
		ret = true;
	}
	else if ((*current)->type == T_PIPE)
	{
		ft_printf_fd(2, E_PARS_PIPE);
		ret = true;
		if ((*current)->next != NULL)
			(*current) = (*current)->next;
	}
	return (ret);
}

bool	operator_error(t_token *current, bool errfound)
{
	if (current->next == NULL && errfound == false)
	{
		ft_printf_fd(2, E_PARS_OPE_E);
		errfound = true;
	}
	else if (current->next != NULL && current->next->type != T_WORD
		&& errfound == false)
	{
		ft_printf_fd(2, E_PARS_OPE_D, current->next->value);
		errfound = true;
	}
	return (errfound);
}

bool	pipe_error(t_minishell *minishell, t_token *current, bool errfound)
{
	if (current->next == NULL && errfound == false)
		ft_printf_fd(2, E_PARS_PIPE);
	else if (current->next != NULL)
	{
		errfound = false;
		check_tokens(minishell, current->next);
	}
	return (errfound);
}
