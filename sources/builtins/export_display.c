/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:15:22 by egache            #+#    #+#             */
/*   Updated: 2025/06/24 13:16:44 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	export_display(t_minishell *minishell)
{
	t_denvp	*current;

	if (minishell->cmds->args[1] == NULL)
	{
		current = minishell->export;
		while (current != NULL && current->var)
		{
			printf("export %s", current->var[0]);
			if (current->var[1] != NULL)
				printf("%s", current->var[1]);
			printf("\n");
			current = current->next;
		}
		return (true);
	}
	return (false);
}
