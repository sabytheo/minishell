/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:43:26 by egache            #+#    #+#             */
/*   Updated: 2025/05/09 15:10:26 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
RELATIVE PATH :

path DEPUIS le dossier actuel
	- contient les ../ et ./ etc...

ABSOLUTE PATH

path depuis le root root
	- /home/egache...

*/
#include "minishell.h"

void	ft_cd(t_minishell *minishell, t_token **tokens)
{
	char	*pwd;
	int		cd;

	(void)minishell;
	pwd = getcwd(NULL, 0);
	printf("pwd before chdir: %s\n", pwd);
	free(pwd);
	if ((*tokens)->next == NULL)
		return ;
	(*tokens) = (*tokens)->next;
	cd = chdir((*tokens)->value);
	pwd = getcwd(NULL, 0);
	printf("pwd after chdir: %s\n", pwd);
	free(pwd);
	if (cd != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n",
			(*tokens)->value);
	}
	return ;
}
