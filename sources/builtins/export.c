/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/06/24 13:23:05 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_variables(char *value)
{
	char	**var;
	int		size1;
	int		size2;

	size1 = ft_strlen_equal(value);
	size2 = ft_strlen(value) - size1;
	var = malloc(sizeof(char *) * 3);
	if (var == NULL)
		return (NULL); // need free
	var[2] = NULL;
	var[0] = ft_strldup(value, size1);
	if (value[size1] != '\0')
		var[1] = ft_strldup(&value[size1], size2);
	else
		var[1] = NULL;
	return (var);
}

bool	already_exist(t_minishell *minishell, t_denvp *list)
{
	t_denvp	*current;
	char	**args;

	args = fill_variables(minishell->cmds->args[1]);
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

static int	export_parsing(char *str)
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

bool	replace_node(t_denvp *current, char *arg)
{
	int	size1;
	int	size2;

	size1 = ft_strlen_equal(arg);
	size2 = ft_strlen(arg) - size1;
	while (current && current->var)
	{
		if (ft_strncmp(arg, current->var[0], size1) == 0)
		{
			if (arg[size1] != '\0')
			{
				free(current->var[1]);
				current->var[1] = ft_strldup(&arg[size1], size2);
			}
			return (true);
		}
		current = current->next;
	}
	return (false);
}

int	ft_export(t_minishell *minishell)
{
	if (export_display(minishell) == true)
		return (0);
	if (already_exist(minishell, minishell->export) == true)
		return (0);
	if (export_parsing(minishell->cmds->args[1]) == 0)
	{
		if (replace_node(minishell->export, minishell->cmds->args[1]) == false)
			add_to_list(minishell, &minishell->export);
		if (replace_node(minishell->envp, minishell->cmds->args[1]) == false)
			add_to_list(minishell, &minishell->envp);
	}
	else if (export_parsing(minishell->cmds->args[1]) == 2)
	{
		if (replace_node(minishell->export, minishell->cmds->args[1]) == false)
			add_to_list(minishell, &minishell->export);
	}
	else
	{
		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
		return (1);
	}
	chainedlst_to_tab(minishell);
	return (0);
}
