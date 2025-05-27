/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:41:43 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 16:32:20 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_tab(void *var)
{
	free_tab((char **)var);
	var = NULL;
}

static void	ft_delnode(void (*del)(void *), t_denvp *to_delete)
{
	(*del)(to_delete->var);
	free(to_delete);
}

static bool	check_arg(char *arg, char *denvp_var)
{
	if (ft_strcmp(arg, denvp_var) == 0)
		return (true);
	return (false);
}

static int	unset_list(t_cmds *cmds, t_denvp **current)

{
	t_denvp *tmp;
	t_denvp *head;

	head = (*current);
	if (check_arg(cmds->args[1], (*current)->var[0]) == true)
	{
		tmp = (*current)->next;
		ft_delnode(del_tab, (*current));
		(*current) = tmp;
		return (0);
	}
	else
	{
		while ((*current) && (*current)->next != NULL)
		{
			if (check_arg(cmds->args[1], (*current)->next->var[0]) == true)
			{
				tmp = (*current)->next->next;
				ft_delnode(del_tab, (*current)->next);
				(*current)->next = tmp;
				(*current) = head;
				return (0);
			}
			else
				(*current) = (*current)->next;
		}
		(*current) = head;
		return (1);
	}
}

int 	ft_unset(t_minishell *minishell)
{
	int ret;
	if (minishell->cmds->args[1] == NULL)
		return (1);
	ret = unset_list(minishell->cmds, &minishell->envp);
	if (ret == 0)
		chainedlst_to_tab(minishell);
	ret = unset_list(minishell->cmds, &minishell->export);
	return (ret);
}
