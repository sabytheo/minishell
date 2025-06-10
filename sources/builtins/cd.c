/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:43:26 by egache            #+#    #+#             */
/*   Updated: 2025/05/28 13:55:40 by egache           ###   ########.fr       */
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
		if (errno == ENOTDIR)
		ft_printf_fd(2, "minishell: cd: %s: Not a directory\n", (*cmds)->args[1]);
	else if (errno == ENOENT)
	ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", (*cmds)->args[1]);
	else if (errno == EACCES)
	ft_printf_fd(2, "minishell: cd: %s: Permission denied\n", (*cmds)->args[1]);
	else
		ft_printf_fd(2, "minishell: cd: %s: %s\n", (*cmds)->args[1], strerror(errno));
	return (1);
	}
	return (0);
}
