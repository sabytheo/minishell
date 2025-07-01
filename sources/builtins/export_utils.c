/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:15:43 by egache            #+#    #+#             */
/*   Updated: 2025/07/01 17:11:41 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

t_denvp	*create_denvp(char **var)
{
	t_denvp	*new;

	new = malloc(sizeof(t_denvp));
	if (!new)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}

void	add_denvp_back(t_denvp **list_denvp, t_denvp *new)
{
	t_denvp	*tmp;

	if (!*list_denvp || !(*list_denvp)->var)
	{
		*list_denvp = new;
		return ;
	}
	tmp = *list_denvp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

bool	valid_id(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (true);
	else
		return (false);
}

void	add_to_list(t_minishell *minishell, t_denvp **list, char *arg)
{
	t_denvp	*current;
	t_denvp	*new;
	char	**var;

	current = *list;
	while (current != NULL && current->next != NULL)
		current = current->next;
	var = fill_variables_export(arg);
	if (var == NULL)
		free_minishell(minishell, E_AFAILED, true);
	new = create_denvp(var);
	if (new == NULL)
	{
		free(var);
		free_minishell(minishell, E_AFAILED, true);
	}
	add_denvp_back(list, new);
}
