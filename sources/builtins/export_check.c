/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:15:22 by egache            #+#    #+#             */
/*   Updated: 2025/06/30 15:33:19 by egache           ###   ########.fr       */
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

bool	already_exist(t_minishell *minishell, t_denvp *list, char *arg)
{
	t_denvp	*current;
	(void)minishell;
	char	**args;

	args = fill_variables(arg);
	if (args == NULL)
		free_minishell(minishell, E_AFAILED, true);
	current = list;
	while (current != NULL && current->var)
	{
		if (ft_strcmp(args[0], list->var[0]) == 0)
		{
			if (ft_strcmp(args[1], list->var[1]) == 0)
			{
				free_tab(args);
				return (true);
			}
		}
		current = current->next;
	}
	free_tab(args);
	return (false);
}

int	export_parsing(char *str)
{
	int	i;

	if (str[0] != '_' && ft_isalpha(str[0]) == 0)
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i = 1;
			while (str[i] != '=')
			{
				if (valid_id(str[i]) == false && ft_isalpha(str[0] == 0))
					return (1);
				i++;
			}
			return (0);
		}
		else if (valid_id(str[i]) == false && ft_isalpha(str[0]) == 0)
			return (1);
		i++;
	}
	return (2);
}
