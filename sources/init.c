/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/13 15:35:18 by tsaby            ###   ########.fr       */
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
	t_envp	*new;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		new = create_node(ft_strdup(envp[i]));
		add_node_back(&minishell->envp, new);
		i++;
	}
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	t_token		*token;
	t_cmds		*cmds;
	t_expand	*expand;
	t_envp		*envp_copy;

	token = NULL;
	cmds = NULL;
	expand = NULL;
	envp_copy = NULL;
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->tokens = token;
	minishell->cmds = cmds;
	minishell->expand = expand;
	minishell->envp = envp_copy;
	minishell->is_running = true;
	minishell->error_code = 0;
	minishell->fd = 0;
	minishell->input_fd = STDIN_FILENO;
	minishell->launch_mode = 0;
	copy_envp(envp, minishell);
	minishell->envp_tab = NULL;
	// print_envp(minishell->envp);
}
