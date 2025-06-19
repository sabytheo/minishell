/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:07:43 by egache            #+#    #+#             */
/*   Updated: 2025/06/19 18:56:15 by egache           ###   ########.fr       */
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
bool	is_numeric_argument(char *str)
{
	int		i;

	if (str[0] == '-' || str[0] == '+' || ft_isdigit(str[0]) == 1)
	{
		i = 1;
		while (str[i])
		{
			if (ft_isdigit(str[i]) == 0)
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

void	ft_exit(t_minishell *minishell, int state)
{
	if (is_numeric_argument(minishell->cmds->args[1]) == false
		&& minishell->cmds->args[1] != NULL)
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			minishell->cmds->args[1]);
		free_minishell(minishell);
		exit(2);
	}
	if (minishell->cmds->args[1] != NULL && minishell->cmds->args[2] != NULL)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		free_minishell(minishell);
		exit(1);
	}
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
