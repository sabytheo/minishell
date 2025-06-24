/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:27:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/24 19:32:48 by tsaby            ###   ########.fr       */
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


	minishell->path = NULL;
	if (is_a_builtins(cmd))
		return (true);
	if (ft_strcmp(cmd,"..") == 0)
		return (false);
	minishell->path = find_path(cmd, minishell->envp_tab, 0);
	if (minishell->path != NULL)
	{
		// if (ft_strcmp(cmd, "./minishell") != 0)
		// {
		// 	free(path);
		// 	path = NULL;
		// }
		if(ft_strnstr(minishell->entry,"|",ft_strlen(minishell->entry)) != NULL)
		{
			free(minishell->path);
			minishell->path = NULL;
		}
		return (true);
	}
	free(minishell->path);
	minishell->path = NULL;
	return (false);
}
