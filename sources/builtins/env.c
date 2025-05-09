/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:17:00 by egache            #+#    #+#             */
/*   Updated: 2025/05/09 16:23:07 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell)
{
	int	i;

	chainedlst_to_tab(minishell, minishell->envp);
	i = 0;
	while (minishell->envp_tab[i] != NULL)
	{
		ft_printf_fd(1, "%s\n", minishell->envp_tab[i]);
		i++;
	}
	return ;
}
