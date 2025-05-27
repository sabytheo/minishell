/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:17:00 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 14:47:33 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell)
{
	t_denvp	*current;

	current = minishell->envp;
	while (current != NULL)
	{
		ft_printf_fd(STDOUT_FILENO, "%s%s\n", current->var[0], current->var[1]);
		current = current->next;
	}
	return ;
}
