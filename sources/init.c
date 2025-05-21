/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/21 18:29:54 by tsaby            ###   ########.fr       */
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

void	copy_envp(char **envp, t_minishell *minishell)
{
	int		i;
	t_envp	*new_envp;
	t_envp	*new_export;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		new_envp = create_node(ft_strdup(envp[i]));
		new_export = create_node(ft_strdup(envp[i]));
		add_node_back(&minishell->envp, new_envp);
		add_node_back(&minishell->export, new_export);
		i++;
	}
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->is_running = true;
	minishell->error_code = 0;
	minishell->input_fd = STDIN_FILENO;
	minishell->output_fd = STDOUT_FILENO;
	minishell->heredoc_fd = STDOUT_FILENO;
	minishell->launch_mode = 0;
	minishell->errfound = false;
	minishell->cmdfound = false;
	minishell->saved_inputfd = -1;
	minishell->saved_outputfd = -1;
	copy_envp(envp, minishell);
}
