/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/06/29 12:49:26 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_args(t_token **current)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (get_cmds_size((*current)) + 1));
	if (args == NULL)
		return (NULL);
	args[get_cmds_size((*current))] = NULL;
	while ((*current) != NULL && (*current)->type != T_PIPE)
	{
		if ((*current)->type >= T_REDIR_IN && (*current)->type <= T_HEREDOC)
			(*current) = (*current)->next;
		else
		{
			args[i] = ft_strdup((*current)->value);
			if (args[i] == NULL)
			{
				free(args);
				return (NULL);
			}
			i++;
		}
		(*current) = (*current)->next;
	}
	return (args);
}

static int	create_redir_token(t_token **current, t_token **redir_token_copy,
		t_token **file_token_copy)
{
	(*redir_token_copy) = duplicate_token(*current);
	if (!(*redir_token_copy))
		return (-1) ;
	*current = (*current)->next;
	(*file_token_copy) = duplicate_token(*current);
	if (!(*file_token_copy))
		return (-1) ;
	*current = (*current)->next;
	(*redir_token_copy)->next = (*file_token_copy);
	(*file_token_copy)->next = NULL;
	return (0);
}
static void	add_redir_to_list(t_token **redir_head, t_token **redir_tail,
		t_token *redir_token_copy, t_token *file_token_copy)
{
	if (!*redir_head)
		*redir_head = redir_token_copy;
	else
		(*redir_tail)->next = redir_token_copy;
	*redir_tail = file_token_copy;
}

t_token	*extract_redirections(t_token **current, t_minishell *minishell, t_cmds *new)
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
			if (create_redir_token(current, &redir_token_copy, &file_token_copy) < 0)
			{
				free_tab(new->args);
				free(new);
				return (free_minishell(minishell, E_AFAILED, true), NULL);
			}
			add_redir_to_list(&redir_head, &redir_tail, redir_token_copy, file_token_copy);
		}
		else
			(*current) = (*current)->next;
	}
	return (redir_head);
}

static void add_and_lastcheck(t_minishell *minishell,t_cmds *new, char **args)
{
	add_cmds_back(&minishell->cmds, new);
	check_ifcmdempty(minishell);
	if (minishell->cmds->args && minishell->cmds->args[0] != NULL)
		new->cmdfound = check_cmd(minishell, args[0]);
}
static void next_tokens(t_token **current_args, t_token **current_redir)
{
		if (*current_args != NULL)
			*current_args = (*current_args)->next;
		if (*current_redir != NULL)
			*current_redir = (*current_redir)->next;
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
		if (!args)
			return (free_minishell(minishell, E_AFAILED, true));
		new = create_cmds(args);
		if (!new)
		{
			free_tab(args);
			return (free_minishell(minishell, E_AFAILED, true));
		}
		new->redirs = extract_redirections(&current_redir,minishell, new);
		add_and_lastcheck(minishell,new,args);
		next_tokens(&current_args,&current_redir);
		if (!current_redir)
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
