/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:42:30 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/13 16:43:33 by egache           ###   ########.fr       */
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

void	print_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		printf("\n NEW NODE \n");
		while (cmds->args[i] != NULL)
		{
			printf("\nargs[%d] : (%s)\n", i, cmds->args[i]);
			i++;
		}
		cmds = cmds->next;
		i = 0;
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
