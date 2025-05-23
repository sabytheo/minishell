/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:41:43 by egache            #+#    #+#             */
/*   Updated: 2025/05/23 18:27:56 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_str(void *value)
{
	free((char *)value);
}

void	ft_delnode(t_envp *envp, void (*del)(void *))
{
	(*del)(envp->value);
	free(envp);
}

static bool	check_arg(char *arg, char *envp_value)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (false);
		i++;
	}
	if (ft_strncmp(arg, envp_value, ft_strlen(arg)) != 0)
		return (false);
	return (true);
}

void	ft_unset(t_minishell *minishell)
{
	t_cmds	*cmds;
	t_envp	*envp;
	t_envp	*current;
	t_envp	*to_delete;

	envp = minishell->envp;
	cmds = minishell->cmds;
	if (cmds->args[1] == NULL)
		return ;
	if (check_arg(cmds->args[1], envp->value) == true)
	{
		to_delete = envp;
		envp = envp->next;
		ft_delnode(to_delete, del_str);
		free(minishell->envp_tab);
		chainedlst_to_tab(minishell, envp);
	}
	else
	{
		current = envp;
		while (current && current->next != NULL)
		{
			if (check_arg(cmds->args[1], current->next->value) == true)
			{
				to_delete = current->next;
				current->next = current->next->next;
				ft_delnode(to_delete, del_str);
				chainedlst_to_tab(minishell, envp);
			}
			else
				current = current->next;
		}
	}
	return ;
}
// current = minishell->envp;
// while (current)
// {
// 	printf("----- %s\n", current->value);
// 	current = current->next;
// }


/*
ft_export :
- Check si arg
	- Si non juste display export; (voir photo yves)

- Check si '=' (export parsing) (SEPARER EN 2 : 1 partie ONLY export 1 partie env & export)
	- Si oui -> export ET env
		- Check si export existe deja
			-strncmp len de l'argument
		- Check si env existe deja
			- strcmp
	- Si non -> export ONLY
		- Check si export existe deja
			-strncmp len de l'argument
	Si toute la string existe deja.
		- Ne rien faire
	Sinon check si la variable existe deja (check jusqu'au egal)
		- Si existe deja : remplacer la string dans le noeud actuel
		- Sinon : rajouter un noeud


void	ft_export(t_minishell *minishell)
{
	if (display_export(minishell) == true)
		return ;
	if (already_exist(minishell) == true)
		return ;
	printf("export parsing : %d\n", export_parsing(minishell->cmds->args[1]));
	if (export_parsing(minishell->cmds->args[1]) == 0)
	{
		if (replace_export(minishell) == false)
			add_to_list(minishell, minishell->export);
		if (replace_envp(minishell) == false)
			add_to_list(minishell, minishell->envp);
		chainedlst_to_tab(minishell, minishell->envp);
	}
	else if (export_parsing(minishell->cmds->args[1]) == 2)
	{
		if (replace_export(minishell) == false)
			add_to_list(minishell, minishell->export);
	}
	else
	{
		minishell->error_code = 1;
		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
	}
	return ;
}
bool	replace_export(t_minishell *minishell)
{
	t_envp	*current;
	int		len;

	current = minishell->export;
	while (current)
	{
		if (ft_strlen_equal(current->value) > ft_strlen_equal(minishell->cmds->args[1]))
			len = ft_strlen_equal(current->value);
		else
			len = ft_strlen_equal(minishell->cmds->args[1]);
		if (ft_strncmp(current->value, minishell->cmds->args[1], len) == 0)
		{//
	return (false);
}

*/

