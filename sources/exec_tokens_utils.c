/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:33 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/13 13:36:45 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmds_size(t_token *tokens)
{
	int	size;

	size = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		tokens = tokens->next;
		size++;
	}
	return (size);
}

t_cmds	*create_cmds(int *type, char **val)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
		return (NULL);
	new->args = val;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_cmds_back(t_cmds **list_cmds, t_cmds *new)
{
	t_cmds	*current;

	if (*list_cmds == NULL)
	{
		*list_cmds = new;
		return ;
	}
	current = *list_cmds;
	while (current->next)
		current = current->next;
	current->next = new;
}
