/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/05/16 18:20:24 by egache           ###   ########.fr       */
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

static int	export_parsing(char *str)
{
	int	i;

	if (ft_isalpha(str[0] == 0))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i = 0;
			while (str[i] != '=')
			{
				if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
					return (0);
				i++;
			}
			return (1);
		}
		else
		{
			if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
				return (0);
			i++;
		}
	}
	return (2);
}
/*
	Si SALUT 		-> puis SALUT=coucou 	-> SALUT=coucou remplace SALUT (dans env et export)
	Si SALUT=coucou -> puis SALUT 		 	-> SALUT ne remplace pas SALUT=coucou (dans env et export)
	Si SALUT=coucou -> puis SALUT=pascoucou -> SALUT=pascoucou remplace SALUT=coucou (dans env et export)
*/

void	add_to_list(t_minishell *minishell, t_envp *list)
{
	t_envp	*current;
	t_envp	*new;
	char	*str;

	current = list;
	printf("list : %p\n", list);
	while (current != NULL && current->next != NULL)
		current = current->next;
	str = ft_strdup(minishell->cmds->args[1]);
	printf("str : %s\n", str);
	new = create_node(str);
	current = list;
	add_node_back(&current, new);
}

void	ft_export(t_minishell *minishell)
{
	t_envp	*current;
	printf("address export : %p\n", minishell->export);
	if (minishell->cmds->args[1] == NULL)
	{
		current = minishell->export;
		while (current)
		{
			printf("export %s\n", current->value);
			current = current->next;
		}
		return ;
	}
	if (export_parsing(minishell->cmds->args[1]) == 1)
	{
		add_to_list(minishell, minishell->envp);
		add_to_list(minishell, minishell->export);
		chainedlst_to_tab(minishell, minishell->envp);
	}
	else if (export_parsing(minishell->cmds->args[1]) == 2)
	{
		add_to_list(minishell, minishell->export);
	}
	else
	{
		minishell->error_code = 1;
		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
	}
	return ;
}
