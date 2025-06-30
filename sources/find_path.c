/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:14:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/30 09:38:23 by tsaby            ###   ########.fr       */
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

char	*find_bin_path(char **path_arg, char *arg)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
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
		path = NULL;
	}
	free_tab(path_arg);
	return (NULL);
}

char	*find_path(char *arg, char **envp)
{
	char	**path_arg;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	if (ft_strnstr(arg, "/", ft_strlen(arg)) != NULL)
	{
		if (access(arg, X_OK) == 0)
			return (ft_strdup(arg));
	}
	path_arg = ft_split(envp[i] + 5, ':');
	if (!path_arg)
		return (NULL);
	path = find_bin_path(path_arg, arg);
	if (path != NULL)
		return (path);
	free(path);
	path = NULL;
	return (NULL);
}

// char	*find_path(char *arg, char **envp)
// {
// 	char	**path_arg;
// 	char	*path;
// 	int i;

// 	i = 0;
// 	path = NULL ;
// 	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
// 		i++;
// 	if (!envp[i])
// 		return (NULL);
// 	if (ft_strnstr(arg, "/", ft_strlen(arg)) != NULL)
// 	{
// 		if (access(arg, X_OK) == 0)
// 			return (ft_strdup(arg));
// 	}
// 	path_arg = ft_split(envp[i] + 5, ':');
// 	i = 0;
// 	while (path_arg != NULL && path_arg[i] && arg)
// 	{
// 		if (arg[0] != '\0')
// 			path = get_a_path(path_arg[i++], arg);
// 		if (!path)
// 		{
// 			free_tab(path_arg);
// 			return (NULL);
// 		}
// 		if (access(path, X_OK) == 0)
// 		{
// 			free_tab(path_arg);
// 			return (path);
// 		}
// 		free(path);
// 		path = NULL;
// 	}
// 	free_tab(path_arg);
// 	return (NULL);
// }
