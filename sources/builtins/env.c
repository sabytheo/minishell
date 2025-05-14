/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:17:00 by egache            #+#    #+#             */
/*   Updated: 2025/05/14 18:55:19 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int fd, t_minishell *minishell)
{
	int	i;

	//chainedlst_to_tab(minishell, minishell->envp);
	i = 0;
	while (minishell->envp_tab[i] != NULL)
	{
		ft_printf_fd(fd, "%s\n", minishell->envp_tab[i]);
		i++;
	}
	return ;
}
