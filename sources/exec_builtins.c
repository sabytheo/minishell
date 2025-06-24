/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:46:38 by egache            #+#    #+#             */
/*   Updated: 2025/06/24 20:46:55 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_minishell *minishell, t_cmds *cmds)
{
	int	len;

	len = ft_strlen(cmds->args[0]);
	if (ft_strncmp(cmds->args[0], "cd", len) == 0 && len == 2)
		minishell->error_code = ft_cd(minishell, &cmds);
	else if (ft_strncmp(cmds->args[0], "echo", len) == 0 && len == 4)
		minishell->error_code = ft_echo(&cmds);
	else if (ft_strncmp(cmds->args[0], "env", len) == 0 && len == 3)
		minishell->error_code = ft_env(minishell);
	else if (ft_strncmp(cmds->args[0], "exit", len) == 0 && len == 4)
		ft_exit(minishell, minishell->error_code);
	else if (ft_strncmp(cmds->args[0], "export", len) == 0 && len == 6)
		minishell->error_code = ft_export(minishell);
	else if (ft_strncmp(cmds->args[0], "pwd", len) == 0 && len == 3)
		minishell->error_code = ft_pwd(minishell);
	else if (ft_strncmp(cmds->args[0], "unset", len) == 0 && len == 5)
		minishell->error_code = ft_unset(minishell);
	return (minishell->error_code);
}
