/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:43:26 by egache            #+#    #+#             */
/*   Updated: 2025/06/30 20:14:10 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
RELATIVE PATH :

path DEPUIS le dossier actuel
	- contient les ../ et ./ etc...

ABSOLUTE PATH

path depuis le root root
	- /home/egache...

// Verifier nombre arg / INterdit > 2
*/

#include "minishell.h"

int	cd_home(t_minishell *minishell)
{
	char	*home;
	t_denvp	*current;
	int		cd;

	current = minishell->envp;
	while (current != NULL)
	{
		if (strcmp("HOME", current->var[0]) == 0)
			home = current->var[1] + 1;
		current = current->next;
	}
	cd = chdir(home);
	if (cd != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: ", home);
		perror(NULL);
		return (1);
	}
	if (update_pwd(minishell) == 1)
		return (1);
	return (0);
}

int	ft_cd(t_minishell *minishell, t_cmds **cmds)
{
	int	cd;
	char *check_pwd;

	if ((*cmds)->args[1] == NULL)
		return (cd_home(minishell));
	else if ((*cmds)->args[2] != NULL)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	check_pwd = getcwd(NULL, 0);
	if (check_pwd == NULL)
		ft_printf_fd(2, E_CHDIR);
	else
		free(check_pwd);
	cd = chdir((*cmds)->args[1]);
	if (cd != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: ", (*cmds)->args[1]);
		perror(NULL);
		return (1);
	}
	if (update_pwd(minishell) == 1)
		return (1);
	return (0);
}
