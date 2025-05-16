/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:56:46 by egache            #+#    #+#             */
/*   Updated: 2025/05/16 15:44:13 by tsaby            ###   ########.fr       */
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

int	ft_echo(int fd, t_cmds **cmds)
{
	bool newline;
	int i;

	newline = false;
	i = 1;
	if ((*cmds) == NULL)
		return (1);
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
		{
			if (newline == false)
				ft_putstr_fd("\n", STDOUT_FILENO);
			i++;
			return (0);
		}
	}
	if (newline == false)
		ft_putstr_fd("\n", fd);
	return (0);
}
