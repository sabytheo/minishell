/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:42:30 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/06 18:45:37 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("---Token: %-15s est de type: %d---\n", tokens->value,
			tokens->type);
		tokens = tokens->next;
	}
}

void	print_envp(t_envp *envp)
{
	while (envp)
	{
		printf("envp: %s\n", envp->value);
		envp = envp->next;
	}
}
