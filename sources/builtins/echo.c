/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:56:46 by egache            #+#    #+#             */
/*   Updated: 2025/07/03 13:19:46 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	find_newline(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = 2;
	if (str != NULL)
	{
		if (ft_strncmp(str, "-n", len) == 0)
		{
			while (str[i] != '\0')
			{
				if (str[i] != 'n')
					return (false);
				i++;
			}
			return (true);
		}
		return (false);
	}
	return (false);
}

int	ft_echo(t_cmds **cmds)
{
	bool	newline;
	int		i;

	newline = false;
	i = 0;
	if ((*cmds) == NULL)
		return (1);
	while (find_newline((*cmds)->args[++i]) == true)
		newline = true;
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
	return (0);
}
