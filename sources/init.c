/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/27 12:51:45 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*create_node(char *val)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (new);
	new->value = val;
	new->next = NULL;
	return (new);
}

void	add_node_back(t_envp **list_envp, t_envp *new)
{
	t_envp	*tmp;

	if (!*list_envp)
	{
		*list_envp = new;
		return ;
	}
	tmp = *list_envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->is_running = true;
	minishell->error_code = 0;
	minishell->input_fd = -1;
	minishell->output_fd = -1;
	minishell->heredoc_fd = -1;
	minishell->saved_inputfd = -1;
	minishell->saved_outputfd = -1;
	minishell->launch_mode = 0;
	minishell->errfound = false;
	minishell->cmdfound = false;
	minishell->cmds_count = 0;
	minishell->saved_inputfd = 0;
	minishell->saved_outputfd = 1;
	split_envp(minishell, envp);
}
