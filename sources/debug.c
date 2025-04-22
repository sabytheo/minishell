/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:42:30 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/22 14:44:07 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_tokens(t_token *tokens)
{
	while (tokens)
		{
			printf("Token: %-15s est de type: %d\n", tokens->value, tokens->type);
			tokens = tokens->next;
		}
}
