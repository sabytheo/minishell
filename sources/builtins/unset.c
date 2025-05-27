/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:41:43 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 14:47:33 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_tab(void *var)
{
	free_tab((char **)var);
	// free(var);
	var = NULL;
}

void	ft_delnode(t_denvp *envp, void (*del)(void *))
{
	(*del)(envp->var);
	free(envp);
}

static bool	check_arg(char *arg, char *denvp_var)
{
	if (ft_strncmp(arg, denvp_var, ft_strlen(denvp_var)) == 0)
		return (true);
	return (false);
}

void	ft_unset(t_minishell *minishell)
{
	t_denvp	*current;
	t_denvp	*to_delete;

	if (minishell->cmds->args[1])
		return ;
	if (check_arg(minishell->cmds->args[1], minishell->envp->var[0]) == true)
	{
		to_delete = minishell->envp;
		minishell->envp = minishell->envp->next;
		ft_delnode(to_delete, del_tab);
		chainedlst_to_tab(minishell);
	}
	else
	{
		current = minishell->envp;
		while (current && current->next != NULL)
		{
			if (check_arg(minishell->cmds->args[1],
					current->next->var[0]) == true)
			{
				to_delete = current->next;
				current->next = current->next->next;
				ft_delnode(to_delete, del_tab);
				chainedlst_to_tab(minishell);
			}
			else
				current = current->next;
		}
	}
	return ;
}

// A REFAIRE
