/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:14:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/05 16:04:14 by tsaby            ###   ########.fr       */
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
