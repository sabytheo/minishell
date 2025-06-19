/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:50:34 by egache            #+#    #+#             */
/*   Updated: 2025/06/19 13:32:45 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_pwd(t_minishell *minishell, t_denvp *list, char *oldpwd)
{
	t_denvp	*current;

	current = list;
	while (current)
	{
		if (ft_strcmp("OLDPWD", current->var[0]) == 0)
		{
			free(current->var[1]);
			current->var[1] = ft_strdup(oldpwd);
			return ;
		}
		current = current->next;
	}
	fill_envpnull(minishell, ft_strjoin("OLDPWD", oldpwd));
	return ;
}

void	new_pwd(t_minishell *minishell, t_denvp *list)
{
	t_denvp	*current;
	char	*oldpwd;
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	current = list;
	while (current)
	{
		if (ft_strcmp("PWD", current->var[0]) == 0)
		{
			oldpwd = ft_strdup(current->var[1]);
			free(current->var[1]);
			current->var[1] = ft_strjoin("=", newpwd);
			old_pwd(minishell, list, oldpwd);
			free(oldpwd);
			free(newpwd);
			return ;
		}
		current = current->next;
	}
	return (free(newpwd));
}


void	update_pwd(t_minishell *minishell)
{
	new_pwd(minishell, minishell->envp);
	new_pwd(minishell, minishell->export);
	chainedlst_to_tab(minishell);
	return ;
}

int	ft_pwd(t_minishell *minishell)
{
	char	*pwd;

	update_pwd(minishell);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	ft_printf_fd(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
