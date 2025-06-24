/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:43:26 by egache            #+#    #+#             */
/*   Updated: 2025/06/24 10:17:36 by tsaby            ###   ########.fr       */
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

int	ft_cd(t_minishell *minishell, t_cmds **cmds)
{
	int		cd;

	if ((*cmds)->args[1] == NULL)
		cd = chdir("/home");
	else if ((*cmds)->args[2] != NULL)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else
	{
		cd = chdir((*cmds)->args[1]);
		update_pwd(minishell);
		if (cd != 0)
		{
			ft_printf_fd(2, "minishell: cd: %s: ", (*cmds)->args[1]);
			perror(NULL);
			return (1);
		}
	}
	return (0);
}
