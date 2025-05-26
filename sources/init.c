/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/26 19:32:39 by egache           ###   ########.fr       */
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

void	split_envp(t_minishell *minishell, char **envp)
{
	t_denvp	*new_denvp;
	t_denvp	*new_export;
	int		i;
	char	**var1;
	char	**var2;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		var1 = fill_variables(envp[i]);
		var2 = fill_variables(envp[i]);
		new_export = create_denvp(var1);
		new_denvp = create_denvp(var2);
		add_denvp_back(&minishell->export, new_export);
		add_denvp_back(&minishell->denvp, new_denvp);
		i++;
	}
	return ;
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
	minishell->saved_inputfd = 0;
	minishell->saved_outputfd = 1;
	split_envp(minishell, envp);
}
