/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/06/24 21:06:34 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((*current)->type >= T_REDIR_IN && (*current)->type <= T_HEREDOC)
			(*current) = (*current)->next;
		else
		{
			args[i] = ft_strdup((*current)->value);
			if (args[i] == NULL)
				return (NULL); // NEED FREE ?
			i++;
		}
		(*current) = (*current)->next;
	}
	return (args);
}

static void	create_redir_token(t_token **current, t_token **redir_token_copy,
		t_token **file_token_copy)
{
	(*redir_token_copy) = duplicate_token(*current);
	if (!(*redir_token_copy))
		return ;
	*current = (*current)->next;
	(*file_token_copy) = duplicate_token(*current);
	if (!(*file_token_copy))
		return ;
	*current = (*current)->next;
	(*redir_token_copy)->next = (*file_token_copy);
	(*file_token_copy)->next = NULL;
	return ;
}

t_token	*extract_redirections(t_token **current)
{
	t_token	*redir_head;
	t_token	*redir_tail;
	t_token	*redir_token_copy;
	t_token	*file_token_copy;

	redir_tail = NULL;
	redir_head = NULL;
	while (*current && (*current)->type != T_PIPE)
	{
		if ((*current)->type >= T_REDIR_IN && (*current)->type <= T_HEREDOC)
		{
			create_redir_token(current, &redir_token_copy, &file_token_copy);
			if (!redir_head)
				redir_head = redir_token_copy;
			else
				redir_tail->next = redir_token_copy;
			redir_tail = file_token_copy;
		}
		else
			(*current) = (*current)->next;
	}
	return (redir_head);
}

void	split_tokens(t_minishell *minishell)
{
	t_token	*current_args;
	t_token	*current_redir;
	t_cmds	*new;
	char	**args;

	current_args = minishell->tokens;
	current_redir = minishell->tokens;
	while (current_args && current_redir)
	{
		args = fill_args(&current_args);
		new = create_cmds(args);
		new->redirs = extract_redirections(&current_redir);
		add_cmds_back(&minishell->cmds, new);
		check_ifcmdempty(minishell);
		if (minishell->cmds->args && minishell->cmds->args[0] != NULL)
			new->cmdfound = check_cmd(minishell, args[0]);
		if (current_args != NULL)
			current_args = current_args->next;
		if (current_redir != NULL)
			current_redir = current_redir->next;
		else
			return ;
	}
	return ;
}

void	exec_tokens(t_minishell *minishell)
{
	t_cmds	*current;

	split_tokens(minishell);
	current = minishell->cmds;
	if (current->next == NULL)
		execute_single_command(minishell);
	else
		execute_piped_command(minishell, current);
	if (minishell->saved_inputfd != -1)
	{
		close(minishell->saved_inputfd);
		minishell->saved_inputfd = -1;
	}
	if (minishell->saved_outputfd != -1)
	{
		close(minishell->saved_outputfd);
		minishell->saved_outputfd = -1;
	}
}
