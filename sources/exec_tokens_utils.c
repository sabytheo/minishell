/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:33 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/13 17:13:43 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmds_size(t_token *tokens)
{
	int	size;

	size = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type >= T_REDIR_IN && tokens->type <= T_HEREDOC)
			tokens = tokens->next;
		else
			size++;
		tokens = tokens->next;
	}
	return (size);
}

t_cmds	*create_cmds(char **val)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
		return (NULL);
	new->args = val;
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
