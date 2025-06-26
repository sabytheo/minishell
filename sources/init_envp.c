/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:40:47 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/26 10:40:58 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_envpnull(t_minishell *minishell, char *var)
{
	t_denvp	*new_denvp;
	t_denvp	*new_export;

	new_export = create_denvp(fill_variables(var));
	if (!new_export)
		return (-1);
	new_denvp = create_denvp(fill_variables(var));
	if (!new_denvp)
	{
		free_tab(new_export->var);
		free(new_export);
		return (-1);
	}
	add_denvp_back(&minishell->export, new_export);
	add_denvp_back(&minishell->envp, new_denvp);
	return (0);
}

static int	create_and_add_denvp(t_minishell *minishell, char **var1,
		char **var2)
{
	t_denvp	*new_denvp;
	t_denvp	*new_export;

	new_export = create_denvp(var1);
	new_denvp = create_denvp(var2);
	if (!new_export || !new_denvp)
	{
		free_tab(var1);
		free_tab(var2);
		if (new_export)
			free(new_export);
		if (new_denvp)
			free(new_denvp);
		return (-1);
	}
	add_denvp_back(&minishell->export, new_export);
	add_denvp_back(&minishell->envp, new_denvp);
	return (0);
}

int	define_shlvl(t_denvp **list)
{
	t_denvp	*current;
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	if (!shlvl)
		return (-1);
	current = (*list);
	while (current)
	{
		if (ft_strcmp("SHLVL", current->var[0]) == 0)
		{
			free(current->var[1]);
			current->var[1] = ft_strjoin("=", shlvl);
			if (!current->var[1])
			{
				free(shlvl);
				return (-1);
			}
			free(shlvl);
			return (0);
		}
		current = current->next;
	}
	free(shlvl);
	return (0);
}

int	fill_envp(t_minishell *minishell, char **envp)
{
	int		i;
	char	**var1;
	char	**var2;

	i = 0;
	var1 = NULL;
	var2 = NULL;
	while (envp[i] != NULL)
	{
		var1 = fill_variables(envp[i]);
		if (!var1)
			return (-1);
		var2 = fill_variables(envp[i]);
		if (!var2)
		{
			free_tab(var1);
			return (-1);
		}
		if (create_and_add_denvp(minishell, var1, var2) == -1)
			return (-1);
		i++;
	}
	return (0);
}
