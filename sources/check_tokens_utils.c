/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:27:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/14 16:52:46 by egache           ###   ########.fr       */
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
	chainedlst_to_tab(minishell, minishell->envp);
	path = find_path(cmd, minishell->envp_tab, 0);
	// printf("path : %s\n", path);
	if (path != NULL)
	{
		free(path);
		return (true);
	}
	free(path);
	return (false);
}

//--------------------------------------------------------------------------------

// bool	check_first_token(t_minishell *minishell, t_token **current)
// {
// 	bool	ret;

// 	ret = false;
// 	if (is_valid_cmd((*current)->value, minishell) == false
// 		&& (*current)->type == T_WORD)
// 	{
// 		ft_printf_fd(2, E_PARS_CMD_NF, (*current)->value);
// 		minishell->error_code = 127;
// 		ret = true;
// 	}
// 	else if ((*current)->type == T_PIPE)
// 	{
// 		ft_printf_fd(2, E_PARS_PIPE);
// 		minishell->error_code = 2;
// 		ret = true;
// 		if ((*current)->next != NULL)
// 			(*current) = (*current)->next;
// 	}
// 	return (ret);
// }

// bool operator_error(t_minishell *minishell, t_token *current, bool errfound)
// {
// 	if (current->next == NULL && errfound == false)
// 	{
// 		ft_printf_fd(2, E_PARS_OPE_E);
// 		minishell->error_code = 2;
// 		errfound = true;
// 	}
// 	else if (current->next != NULL && current->next->type != T_WORD
//		&& errfound == false)
// 	{
// 		ft_printf_fd(2, E_PARS_OPE_D, current->next->value);
// 		// printf("current->next->value in operator error : %s\n",
//			current->next->value);
// 		minishell->error_code = 2;
// 		errfound = true;
// 	}
// 	return (errfound);
// }

// bool pipe_error(t_minishell *minishell, t_token *current, bool errfound)
// {
// 	if (current->next == NULL && errfound == false)
// 	{
// 		ft_printf_fd(2, E_PARS_PIPE);
// 		minishell->error_code = 2;
// 	}
// 	else if (current->next != NULL)
// 	{
// 		// errfound = false;
// 		// printf("current->next in pipe_error : %s\n", current->next->value);
// 		check_tokens(minishell, current->next);
// 	}
// 	return (errfound);
// }
