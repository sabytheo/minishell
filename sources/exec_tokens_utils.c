/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:33 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/01 16:02:49 by tsaby            ###   ########.fr       */
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

void	add_and_lastcheck(t_minishell *minishell, t_cmds *new, char **args)
{
	add_cmds_back(&minishell->cmds, new);
	check_ifcmdempty(minishell);
	if (minishell->cmds->args && minishell->cmds->args[0] != NULL)
		new->cmdfound = check_cmd(minishell, args[0]);
}

void	next_tokens(t_token **current_args, t_token **current_redir)
{
	if (*current_args != NULL)
		*current_args = (*current_args)->next;
	if (*current_redir != NULL)
		*current_redir = (*current_redir)->next;
}

void	add_redir_to_list(t_token **redir_head, t_token **redir_tail,
		t_token *redir_token_copy, t_token *file_token_copy)
{
	if (!*redir_head)
		*redir_head = redir_token_copy;
	else
		(*redir_tail)->next = redir_token_copy;
	*redir_tail = file_token_copy;
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
