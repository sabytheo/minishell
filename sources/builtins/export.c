/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/07/02 15:29:33 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_variables_tab_null(char **var)
{
	free_tab(var);
	return (NULL);
}

bool	replace_node_envp(t_minishell *minishell, t_denvp *current, char *arg)
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

void	export_add_envp(t_minishell *minishell, t_denvp **envp, char *arg)
{
	if (replace_node_envp(minishell, (*envp), arg) == false)
		add_to_list_envp(minishell, envp, arg);
}

char	**fill_variables_envp(char *value)
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
		return (free_variables_tab_null(var));
	if (value[size1] != '\0')
	{
		var[1] = ft_strldup(&value[size1], size2);
		if (var[1] == NULL)
			return (free_variables_tab_null(var));
	}
	else
		var[1] = NULL;
	return (var);
}

int	ft_export(t_minishell *minishell, t_cmds *cmds)
{
	int	i;

	i = 0;
	if (export_display(minishell) == true)
		return (0);
	while (cmds->args[++i] != NULL)
	{
		if (already_exist(minishell, minishell->export, cmds->args[i]) == false)
		{
			if (export_parsing(cmds->args[i]) == 0)
			{
				export_add_export(minishell, &minishell->export, cmds->args[i]);
				export_add_envp(minishell, &minishell->envp, cmds->args[i]);
			}
			else if (export_parsing(cmds->args[i]) == 2)
				export_add_export(minishell, &minishell->export, cmds->args[i]);
			else
			{
				ft_printf_fd(2, E_EXPORT_ARG, cmds->args[i]);
				return (1);
			}
		}
	}
	chainedlst_to_tab(minishell);
	return (0);
}
