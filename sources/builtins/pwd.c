/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:50:34 by egache            #+#    #+#             */
/*   Updated: 2025/07/01 12:38:55 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int old_pwd(t_minishell *minishell, t_denvp *list, char *oldpwd)
{
	t_denvp *current;
	char *var;

	current = list;
	while (current)
	{
		if (ft_strcmp("OLDPWD", current->var[0]) == 0)
		{
			free(current->var[1]);
			current->var[1] = ft_strdup(oldpwd);
			free(oldpwd);
			if (current->var[1] == NULL)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	var = ft_strjoin("OLDPWD", oldpwd);
	free(oldpwd);
	if (var == NULL)
		return (-1);
	if (fill_envpnull(minishell, var) == -1)
		return (-1);
	return (0);
}

int new_pwd(t_minishell *minishell, t_denvp *list, char *newpwd)
{
	t_denvp *current;
	char *oldpwd;

	current = list;
	while (current)
	{
		if (ft_strcmp("PWD", current->var[0]) == 0)
		{
			oldpwd = ft_strdup(current->var[1]);
			if (oldpwd == NULL)
				return (-1);
			free(current->var[1]);
			current->var[1] = ft_strjoin("=", newpwd);
			if (current->var[1] == NULL)
			{
				free(oldpwd);
				return (-1);
			}
			if (old_pwd(minishell, list, oldpwd) == -1)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

int update_pwd(t_minishell *minishell)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf_fd(2, E_NOPWD, "minishell");
		return (1);
	}
	if (new_pwd(minishell, minishell->envp, pwd) == -1)
	{
		free(pwd);
		free_minishell(minishell, E_AFAILED, true);
	}
	if (new_pwd(minishell, minishell->export, pwd) == -1)
	{
		free(pwd);
		free_minishell(minishell, E_AFAILED, true);
	}
	chainedlst_to_tab(minishell);
	free(pwd);
	return (0);
}

int ft_pwd(t_minishell *minishell)
{
	char *pwd;

	(void)minishell;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf_fd(2, E_NOPWD, "minishell");
		return (1);
	}
	ft_printf_fd(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
