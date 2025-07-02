/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:15:22 by egache            #+#    #+#             */
/*   Updated: 2025/07/02 14:29:45 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_variables_tab_int(char **var, int ret)
{
	free_tab(var);
	return (ret);
}

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
	char	**args;

	args = fill_variables_export(arg);
	if (args == NULL)
		free_minishell(minishell, E_AFAILED, true);
	current = list;
	while (current != NULL && current->var != NULL)
	{
		if (ft_strcmp(args[0], current->var[0]) == 0)
		{
			if (current->var[1] != NULL && args[1] != NULL)
			{
				if (ft_strcmp(args[1], current->var[1]) == 0)
					return (free_variables_tab_int(args, 1));
			}
			if (args[1] == NULL)
				return (free_variables_tab_int(args, 1));
		}
		current = current->next;
	}
	free_tab(args);
	return (false);
}

bool	valid_id(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (true);
	else
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
				if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
					return (1);
				i++;
			}
			return (0);
		}
		else if (valid_id(str[i]) == false || ft_isalpha(str[0]) == 0)
			return (1);
		i++;
	}
	return (2);
}
