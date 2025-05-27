/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:07:43 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 17:25:31 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Bash builtins return an exit status of zero
if they succeed and a non-zero status on failure
*/

/*
Check if arg is numeric value
	If not ret is 2 and print bash: exit: hello: numeric argument required
Check nbr of arg
	if > 2 ret is 1 and print "bash: exit: too many arguments\n"

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
