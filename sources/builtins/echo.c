/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:56:46 by egache            #+#    #+#             */
/*   Updated: 2025/05/06 14:58:54 by egache           ###   ########.fr       */
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

void	ft_echo(t_token *tokens)
{
	int	newline;

	newline = 0;
	if (tokens == NULL || tokens->next == NULL)
		return ;
	tokens = tokens->next;
	newline = find_newline(tokens->value);
	if (newline == true && tokens->next != NULL)
		tokens = tokens->next;
	while (tokens && tokens->type == T_WORD)
	{
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		if (tokens->next != NULL)
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
			tokens = tokens->next;
		}
		else
		{
			if (newline == false)
				ft_putstr_fd("\n", STDOUT_FILENO);
			return ;
		}
	}
	return ;
}
