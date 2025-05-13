/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:56:46 by egache            #+#    #+#             */
/*   Updated: 2025/05/13 16:37:31 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static bool	find_newline(char *str)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (ft_strncmp(str, "-n", len) == 0 && len == 2)
// 		return (true);
// 	return (false);
// }

// void	ft_echo(t_cmds **cmds)
// {
// 	int	newline;

// 	newline = 0;
// 	if ((*cmds) == NULL || (*cmds)->next == NULL)
// 		return ;
// 	(*cmds) = (*cmds)->next;
// 	newline = find_newline((*cmds)->value);
// 	if (newline == true && (*cmds)->next != NULL)
// 		(*cmds) = (*cmds)->next;
// 	while ((*cmds) && (*cmds)->type == T_WORD)
// 	{
// 		ft_putstr_fd((*cmds)->value, STDOUT_FILENO);
// 		if ((*cmds)->next != NULL)
// 		{
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 			(*cmds) = (*cmds)->next;
// 		//ft_printf("\nvaleur token dans echo : %s\n\n", (*cmds)->value);
// 		}
// 		else
// 		{
// 			if (newline == false)
// 				ft_putstr_fd("\n", STDOUT_FILENO);
// 			return ;
// 		}
// 	}
// 	return ;
// }
