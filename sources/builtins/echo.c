/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:56:46 by egache            #+#    #+#             */
/*   Updated: 2025/04/30 20:04:21 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_echo(t_token *tokens)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	str[0] = '\0';
	if (!tokens || !tokens->next)
		return (NULL);
	tokens = tokens->next;
	while (tokens && tokens->type == T_WORD)
	{
		str = ft_strjoin(str, tokens->value);
		if (tokens->next != NULL)
		{
			str = ft_strjoin(str, " ");
			tokens = tokens->next;
		}
		else
			return (str);
	}
	return (str);
}
