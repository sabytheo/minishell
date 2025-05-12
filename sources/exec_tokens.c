/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/05/12 19:57:48 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_tokens(t_minishell *minishell, t_token *tokens)
// {
// }

static int	get_cmds_size(t_token *tokens)
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

static char	**fill_args(t_token **current)
{
	char	**args;
	int		i;
	int		size;

	i = 0;
	size = get_cmds_size((*current));
	args = malloc(sizeof(char *) * (size + 1));
	if (args == NULL)
		return (NULL); // NEED FREE ?
	args[size] = NULL;
	while ((*current) != NULL && (*current)->type != T_PIPE)
	{
		args[i] = ft_strdup((*current)->value);
		if (args[i] == NULL)
			return (NULL); // NEED FREE ?
		(*current) = (*current)->next;
		i++;
	}
	return (args);
}

void	split_tokens(t_token *tokens, t_minishell *minishell)
{
	t_token	*current;
	t_cmds	*new;
	char	**args;

	current = tokens;
	while (current != NULL)
	{
		args = fill_args(&current);
		new = create_cmds(args);
		add_cmds_back(&minishell->cmds, new);
		if (current != NULL)
			current = current->next;
		else
			return ;
	}
	return ;
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
