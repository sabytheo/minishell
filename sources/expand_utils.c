/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/15 19:33:48 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c, int len)
{
	if (len == 0)
		return (ft_isalpha(c) || c == '_' || c == '?');
	return (ft_isalnum(c) || c == '_');
}

int	envp_size(t_envp *envp)
{
	t_envp	*tmp;
	int		len;

	len = 0;
	tmp = envp;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	free(tmp);
	return (len);
}

void	chainedlst_to_tab(t_minishell *minishell, t_envp *envp)
{
	char	**envp_tab_copy;
	t_envp	*current;
	int		i;

	minishell->envp_countline = envp_size(envp);
	current = envp;
	i = 0;
	envp_tab_copy = malloc(sizeof(char *) * (minishell->envp_countline + 1));
	if (envp_tab_copy == NULL)
		return ;
	while (current)
	{
		envp_tab_copy[i] = current->value;
		i++;
		current = current->next;
	}
	envp_tab_copy[i] = NULL;
	if (minishell->envp_tab)
		free(minishell->envp_tab);
	minishell->envp_tab = envp_tab_copy;
}
