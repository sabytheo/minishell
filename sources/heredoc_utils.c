/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:19:50 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/02 17:19:43 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*create_heredoc_node(char *filename)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (new == NULL)
		return (NULL);
	new->filename = filename;
	new->next = NULL;
	return (new);
}

void	add_heredoc_back(t_heredoc **list_heredoc, t_heredoc *new)
{
	t_heredoc	*current;

	if (!*list_heredoc)
	{
		*list_heredoc = new;
		return ;
	}
	current = *list_heredoc;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	cleanup_heredocs(t_minishell *minishell)
{
	t_heredoc	*current;
	t_heredoc	*tmp;

	current = minishell->heredoc;
	while (current)
	{
		unlink(current->filename);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	minishell->heredoc = NULL;
}

int	create_list_heredoc(char *filename, t_minishell *minishell)
{
	t_heredoc	*new;

	new = create_heredoc_node(filename);
	if (!new)
	{
		unlink(filename);
		return (-1);
	}
	add_heredoc_back(&minishell->heredoc, new);
	return (0);
}
