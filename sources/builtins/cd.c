/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:43:26 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 17:20:58 by egache           ###   ########.fr       */
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

int	ft_cd(t_cmds **cmds)
{
	char	*pwd;
	int		cd;

	pwd = getcwd(NULL, 0);
	free(pwd);
	if ((*cmds)->args[1] == NULL)
		cd = chdir("/home");
	else
		cd = chdir((*cmds)->args[1]);
	pwd = getcwd(NULL, 0);
	free(pwd);
	if (cd != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n",
			(*cmds)->args[1]);
		return (1);
	}
	return (0);
}
