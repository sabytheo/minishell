/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:17:00 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 16:45:47 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *minishell)
{
	t_denvp	*current;

	current = minishell->envp;
	if (minishell->cmds->args[1] != NULL)
		return (127);
	while (current != NULL)
	{
		ft_printf_fd(STDOUT_FILENO, "%s%s\n", current->var[0], current->var[1]);
		current = current->next;
	}
	return (0);
}
