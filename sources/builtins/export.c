/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/05/14 19:22:09 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_id(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (true);
	else
		return (false);
}

static bool	export_parsing(char *str)
{
	int	i;

	if (ft_isalpha(str[0] == 0))
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i = 0;
			while (str[i] != '=')
			{
				if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
					return (false);
				i++;
			}
			return (true);
		}
		i++;
	}
	return (false);
}

void	ft_export(t_minishell *minishell)
{
	t_envp	*current;
	t_envp	*new;
	// int		i;

	current = minishell->envp;
	while (current->next != NULL)
		current = current->next;
	if (export_parsing(minishell->cmds->args[1]) == true)
	{
		new = create_node(minishell->cmds->args[1]);
		add_node_back(&current, new);
		chainedlst_to_tab(minishell, minishell->envp);
	}
	// current = minishell->envp;
	// i = 0;
	// while (current)
	// {
	// 	printf("///// %s\n", minishell->envp->value);
	// 	printf("----- %s\n", current->value);
	// 	minishell->envp = minishell->envp->next;
	// 	current = current->next;
	// }
	// while (minishell->envp_tab[i] != NULL)
	// {
	// 	printf("+++++ %s\n", minishell->envp_tab[i]);
	// 	i++;
	// }
	return ;
}
