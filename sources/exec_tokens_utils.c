/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:33 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/24 17:42:35 by egache           ###   ########.fr       */
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
	new->redirs = NULL;
	new->cmdfound = false;
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

t_token	*duplicate_token(t_token *token)
{
	t_token	*new_token;

	if (!token)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	new_token->value = ft_strdup(token->value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}
