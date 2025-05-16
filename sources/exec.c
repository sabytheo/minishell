/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:14:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/16 09:23:39 by tsaby            ###   ########.fr       */
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

	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	if (access(arg, X_OK) == 0)
		return (arg);
	path_arg = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_arg != NULL && path_arg[i] && arg)
	{
		path = get_a_path(path_arg[i++], arg);
		if (!path)
			return (NULL);
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

int	exec_builtins(t_minishell *minishell)
{
	int		len;
	int		fd;
	t_cmds	*cmds;

	if (minishell->fd != 0)
		fd = minishell->fd;
	else
		fd = STDOUT_FILENO;
	cmds = minishell->cmds;
	len = ft_strlen(cmds->args[0]);
	// if (ft_strncmp(cmds->args[0], "cd", len) == 0 && len == 2)
	// 	ft_cd(&cmds);
	if (ft_strncmp(cmds->args[0], "echo", len) == 0 && len == 4)
		ft_echo(fd, &cmds);
	// else if (ft_strncmp(cmds->args[0], "env", len) == 0 && len == 3)
	// 	ft_env(fd, minishell);
	// else if (ft_strncmp(cmds->args[0], "exit", len) == 0 && len == 4)
	// 	return ;
	// else if (ft_strncmp(cmds->args[0], "export", len) == 0 && len == 6)
	// 	ft_export(minishell);
	// else if (ft_strncmp(cmds->args[0], "pwd", len) == 0 && len == 3)
	// 	ft_pwd();
	// else if (ft_strncmp(cmds->args[0], "unset", len) == 0 && len == 5)
	// 	ft_unset(minishell);
	return (0);
}
