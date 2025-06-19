/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:14:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/19 15:59:37 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_a_path(char *path_arg, char *arg)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(path_arg, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, arg);
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (path);
}

char	*find_path(char *arg, char **envp, int i)
{
	char	**path_arg;
	char	*path;

	path = NULL ;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	if (ft_strnstr(arg, "/", ft_strlen(arg)) != NULL)
	{
		if (access(arg, X_OK) == 0)
			return (arg);
	}
	path_arg = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_arg != NULL && path_arg[i] && arg)
	{
		if (arg[0] != '\0')
			path = get_a_path(path_arg[i++], arg);
		if (!path)
		{
			free_tab(path_arg);
			return (NULL);
		}
		if (access(path, X_OK) == 0)
		{
			free_tab(path_arg);
			return (path);
		}
		free(path);
	}
	free_tab(path_arg);
	return (NULL);
}

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
