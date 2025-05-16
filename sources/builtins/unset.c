/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:41:43 by egache            #+#    #+#             */
/*   Updated: 2025/05/16 12:31:53 by egache           ###   ########.fr       */
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
