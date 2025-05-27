/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:07:43 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 17:02:07 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Bash builtins return an exit status of zero
if they succeed and a non-zero status on failure
*/

void	ft_exit(t_minishell *minishell, int state)
{
	if (minishell->cmds->args[1] == NULL)
	{
		free_minishell(minishell);
		exit(state);
	}
	else
	{
		minishell->error_code = ft_atoi(minishell->cmds->args[1]);
		free_minishell(minishell);
		exit(minishell->error_code);
	}
}
