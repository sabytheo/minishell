/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:32:19 by egache            #+#    #+#             */
/*   Updated: 2025/06/25 14:16:29 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ifcmdempty(t_minishell *minishell)
{
	int	i;

	if (!minishell || !minishell->cmds || !minishell->cmds->args)
		return ;
	if (!minishell->cmds->args[0])
		return ;
	if (minishell->cmds->args[0][0] == '\0')
	{
		free(minishell->cmds->args[0]);
		i = 0;
		while (minishell->cmds->args[i + 1] != NULL)
		{
			minishell->cmds->args[i] = minishell->cmds->args[i + 1];
			i++;
		}
		minishell->cmds->args[i] = NULL;
	}
}

bool	check_filetype(t_minishell *minishell, char *arg)
{
	struct stat	fs;

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
	return (false);
}

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
	if (ft_strcmp("..", cmd) == 0)
		return (false);
	if (is_a_builtins(cmd))
		return (true);
	minishell->path = find_path(cmd, minishell->envp_tab);
	if (minishell->path != NULL)
	{
		if (ft_strnstr(minishell->entry, "|",
				ft_strlen(minishell->entry)) != NULL)
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

bool	check_cmd(t_minishell *minishell, char *arg)
{
	if (ft_strcmp(arg, ".") == 0)
	{
		ft_printf_fd(2, "minishell: %s : check the usage\n", arg);
		return (false);
	}
	else if (ft_strncmp("./", arg, 2) == 0 || ft_strncmp("/", arg, 1) == 0
		|| ft_strncmp("../", arg, 3) == 0)
		return (check_filetype(minishell, arg));
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
