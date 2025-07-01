/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainedlst_totab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:01:28 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/26 15:09:04 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_size(t_denvp *envp)
{
	t_denvp	*current;
	int		len;

	len = 0;
	current = envp;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	free(current);
	return (len);
}

static void	cleanup_tab_and_exit(t_minishell *minishell, int index)
{
	int	j;

	j = 0;
	while (j <= index)
		free(minishell->envp_tab[j++]);
	*minishell->envp_tab = NULL;
	return (free_minishell(minishell, E_AFAILED, true));
}

void	chainedlst_to_tab(t_minishell *minishell)
{
	t_denvp	*current;
	int		i;

	if (minishell->envp_tab)
		free_tab(minishell->envp_tab);
	minishell->envp_countline = envp_size(minishell->envp);
	current = minishell->envp;
	i = 0;
	minishell->envp_tab = malloc(sizeof(char *) * (minishell->envp_countline
				+ 1));
	if (minishell->envp_tab == NULL)
		return (free_minishell(minishell, E_AFAILED, true));
	while (current && current->var)
	{
		minishell->envp_tab[i] = ft_strjoin(current->var[0], current->var[1]);
		if (!minishell->envp_tab[i])
			cleanup_tab_and_exit(minishell, i);
		i++;
		current = current->next;
	}
	minishell->envp_tab[i] = NULL;
}
