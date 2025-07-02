/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:12:27 by egache            #+#    #+#             */
/*   Updated: 2025/07/02 18:15:30 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_variable_export(char *var, char *arg, int size1, int size2)
{
	char	*tmp;

	tmp = NULL;
	free(var);
	var = ft_strldup(&arg[size1 + 1], size2);
	if (var == NULL)
		return (NULL);
	tmp = ft_strjoin("=\"", var);
	free(var);
	if (tmp == NULL)
		return (NULL);
	var = ft_strjoin(tmp, "\"");
	free(tmp);
	if (var == NULL)
		return (NULL);
	return (var);
}

static bool	replace_node_export(t_minishell *minishell, t_denvp *current,
		char *arg)
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
				current->var[1] = replace_variable_export(current->var[1], arg,
						size1, size2);
				if (current->var[1] == NULL)
					free_minishell(minishell, E_AFAILED, true);
			}
			return (true);
		}
		current = current->next;
	}
	return (false);
}

static char	**join_and_dup_export(char **var, char *value, int size1, int size2)
{
	char	*tmp;

	tmp = NULL;
	var[1] = ft_strldup(&value[size1 + 1], size2);
	if (var[1] == NULL)
		return (free_variables_tab_null(var));
	tmp = ft_strjoin("=\"", var[1]);
	if (tmp == NULL)
		return (free_variables_tab_null(var));
	free(var[1]);
	var[1] = ft_strjoin(tmp, "\"");
	free(tmp);
	if (var[1] == NULL)
		return (free_variables_tab_null(var));
	return (var);
}

void	export_add_export(t_minishell *minishell, t_denvp **export, char *arg)
{
	if (replace_node_export(minishell, (*export), arg) == false)
		add_to_list_export(minishell, export, arg);
}

char	**fill_variables_export(char *value)
{
	char	**var;
	int		size1;
	int		size2;
	char	*tmp;

	tmp = NULL;
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
		return (join_and_dup_export(var, value, size1, size2));
	else
		var[1] = NULL;
	return (var);
}
