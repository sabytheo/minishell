/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/05/20 20:25:49 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i = 0;
			while (str[i] != '=')
			{
				if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
					return (1);
				i++;
			}
			return (0);
		}
		else
		{
			if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
				return (1);
			i++;
		}
	}
	return (2);
}
/*
	Si SALUT 		-> puis SALUT=coucou 	-> SALUT=coucou remplace SALUT (dans env et export)
	Si SALUT=coucou
						-> puis SALUT 				-> SALUT ne remplace pas SALUT=coucou (dans env et export)
	Si SALUT=coucou -> puis SALUT=pascoucou
		-> SALUT=pascoucou remplace SALUT=coucou (dans env et export)
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

bool	display_export(t_minishell *minishell)
{
	t_envp	*current;

	if (minishell->cmds->args[1] == NULL)
	{
		current = minishell->export;
		while (current)
		{
			printf("export %s\n", current->value);
			current = current->next;
		}
		return (true);
	}
	return (false);
}

int	ft_strlen_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

bool	replace_export(t_minishell *minishell)
{
	t_envp	*current;

	current = minishell->envp;
	while (current != NULL)
	{
		if (ft_strncmp(minishell->cmds->args[1], current->value,
				(ft_strlen_equal(current->value) + 1)) == 0)
		{
			free(current->value);
			current->value = ft_strdup(minishell->cmds->args[1]);
			chainedlst_to_tab(minishell, minishell->envp);
		}
		current = current->next;
	}
	current = minishell->export;
	while (current != NULL)
	{
		if (ft_strncmp(minishell->cmds->args[1], current->value,
				ft_strlen_equal(current->value)) == 0)
		{
			free(current->value);
			current->value = ft_strdup(minishell->cmds->args[1]);
			return (true);
		}
		current = current->next;
	}
	return (false);
}

bool	already_exist(t_minishell *minishell)
{
	t_envp	*current;

	current = minishell->envp;
	while (current)
	{
		if (ft_strcmp(minishell->cmds->args[1], current->value) == 0)
			return (true);
		current = current->next;
	}
	current = minishell->export;
	while (current)
	{
		if (ft_strcmp(minishell->cmds->args[1], current->value) == 0)
			return (true);
		current = current->next;
	}
	if (export_parsing(minishell->cmds->args[1]) == 2)
	{
		current = minishell->export;
		while (current)
		{
			if (ft_strncmp(minishell->cmds->args[1], current->value,
					ft_strlen_equal(minishell->cmds->args[1]) == 0))
				return (true);
		}
	}
	return (false);
}

// void	ft_export(t_minishell *minishell)
// {
// 	if (display_export(minishell) == true)
// 		return ;
// 	if (export_parsing(minishell->cmds->args[1]) == 0)
// 	{
// 		if (replace_export(minishell) == true)
// 			return ;
// 		add_to_list(minishell, minishell->envp);
// 		add_to_list(minishell, minishell->export);
// 		chainedlst_to_tab(minishell, minishell->envp);
// 	}
// 	else if (export_parsing(minishell->cmds->args[1]) == 2)
// 	{
// 		if (replace_export(minishell) == true)
// 			return ;
// 		add_to_list(minishell, minishell->export);
// 	}
// 	else
// 	{
// 		minishell->error_code = 1;
// 		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
// 	}
// 	return ;
// }

void	ft_export(t_minishell *minishell)
{
	if (display_export(minishell) == true)
		return ;
	if (already_exist(minishell) == true)
		return ;
	if (export_parsing(minishell->cmds->args[1]) == 0)
	{
		if (replace_export(minishell) == true)
			return ;
		add_to_list(minishell, minishell->envp);
		add_to_list(minishell, minishell->export);
		chainedlst_to_tab(minishell, minishell->envp);
	}
	else if (export_parsing(minishell->cmds->args[1]) == 2)
		add_to_list(minishell, minishell->export);
	else
	{
		minishell->error_code = 1;
		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
	}
	return ;
}
