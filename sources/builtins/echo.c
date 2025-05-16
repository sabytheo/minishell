/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:56:46 by egache            #+#    #+#             */
/*   Updated: 2025/05/16 16:54:21 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	find_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "-n", len) == 0 && len == 2)
		return (true);
	return (false);
}

void	ft_echo(t_minishell *minishell, t_cmds **cmds)
{
	bool	newline;
	int		i;

	(void)minishell;
	newline = false;
	i = 1;
	if ((*cmds) == NULL)
		return ;
	newline = find_newline((*cmds)->args[i]);
	if (newline == true)
		i++;
	while ((*cmds)->args[i] != NULL)
	{
		ft_putstr_fd((*cmds)->args[i], STDOUT_FILENO);
		if ((*cmds)->args[i + 1] != NULL)
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		else
			i++;
	}
	if (newline == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return ;
}
