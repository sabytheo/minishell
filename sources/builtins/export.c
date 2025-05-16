/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/05/16 13:42:07 by egache           ###   ########.fr       */
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

/*
	export A123 n'est pas une erreur
	Pas forcement de =
		- La variable ne sera seulement pas mis dans le env mais seulement dans export

*/

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
export sans argument -> liste tous les exports
	- par exemple si j'export "kk" mais aucune valeur associe
	- l'export "fonctionne" mais la variable n'est pas affiche dans env
	- parcontre "export" sans argument listera kk et toutes les autres variables
	- kk= est valide et sera bien affiche dans env
*/

void	add_to_list(t_minishell *minishell, t_envp *list)
{
	t_envp	*current;
	t_envp	*new;
	char	*str;

	current = list;
	printf("list : %p\n", list);
	while (current != NULL && current->next != NULL)
	{
		current = current->next;
	}
	str = ft_strdup(minishell->cmds->args[1]);
	printf("str : %s\n", str);
	new = create_node(str);
	add_node_back(&current, new);
	current = list;
}
/* qques leak mais normal -- la liste export ne fonctionne pas atm. */

void	ft_export(t_minishell *minishell)
{
	t_envp	*current;

	minishell->export = ft_calloc(1, sizeof(t_envp));
	printf("address export : %p\n", minishell->export);
	printf("address envp   : %p\n", minishell->envp);
	if (minishell->cmds->args[1] == NULL)
	{
		current = minishell->export;
		printf("caca\n");
		printf("export -- %s\n", current->value);
		while (current)
		{
			printf("export %s\n", current->value);
			current = current->next;
		}
		return ;
	}
	if (export_parsing(minishell->cmds->args[1]) == 1)
	{
		printf("pipi\n");
		// add_to_list(minishell, minishell->export);
		add_to_list(minishell, minishell->envp);
		print_envp(minishell->envp);
		chainedlst_to_tab(minishell, minishell->envp);
	}
	else if (export_parsing(minishell->cmds->args[1]) == 2)
	{
		printf("caca\n");
		add_to_list(minishell, minishell->export);
	}
	else
	{
		minishell->error_code = 1;
		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
	}
	return ;
}
