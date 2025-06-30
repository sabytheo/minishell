/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/06/30 18:43:55 by egache           ###   ########.fr       */
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
		return (NULL);
	var[2] = NULL;
	var[0] = ft_strldup(value, size1);
	if (var[0] == NULL)
	{
		free(var);
		return (NULL);
	}
	if (value[size1] != '\0')
	{
		var[1] = ft_strldup(&value[size1], size2);
		if (var[1] == NULL)
		{
			free_tab(var);
			return (NULL);
		}
	}
	else
		var[1] = NULL;
	return (var);
}

bool	replace_node(t_minishell *minishell, t_denvp *current, char *arg)
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
				if (current->var[1] == NULL)
					free_minishell(minishell, E_AFAILED, true);
			}
			return (true);
		}
		current = current->next;
	}
	return (false);
}

void	export_add(t_minishell *minishell, t_denvp **list, char *arg)
{
	if (replace_node(minishell, (*list), arg) == false)
		add_to_list(minishell, list, arg);
		
}

int	ft_export(t_minishell *minishell)
{
	int i;

	i = 1;
	if (export_display(minishell) == true)
		return (0);
	while (already_exist(minishell, minishell->export, minishell->cmds->args[i]) == true)
		i++;
	while (minishell->cmds->args[i] != NULL)
	{
		if (export_parsing(minishell->cmds->args[i]) == 0)
		{
			export_add(minishell, &minishell->export, minishell->cmds->args[i]);
			export_add(minishell, &minishell->envp, minishell->cmds->args[i]);
		}
		else if (export_parsing(minishell->cmds->args[i]) == 2)
			export_add(minishell, &minishell->export, minishell->cmds->args[i]);
		else
			ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[i]);
		i++;
	}
	chainedlst_to_tab(minishell);
	return (0);
}
