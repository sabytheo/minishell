/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:42:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/19 16:48:59 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
static t_token_type	get_type(char *str)
{
	if (!str)
		return (T_WORD);
	if (ft_strncmp(str, "|", 2) == 0)
		return (T_PIPE);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (T_APPEND);
	if (ft_strncmp(str, "<", 2) == 0)
		return (T_REDIR_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (T_REDIR_OUT);
	return (T_WORD);
}

static char *extract_token (char *entry, int *i)
{
	int start;
	char quote;

	while (entry[*i] && entry[*i] == ' ')
		(*i)++;
	if (is_operator(entry[*i]) == true)
	{
		start = *i;
		if ((entry[*i] == '<' || entry[*i] == '>' ) && entry[*i] == entry[*i + 1])
		{
			*i += 2;
			return (ft_substr(entry,start, 2));
		}
		*i += 1;
		return (ft_substr(entry,start, 1));
	}
	start = *i;
	while(entry[*i])
	{
		if (entry[*i] == '\'' || entry[*i] == '"')
		{
			quote = entry[*i];
			(*i)++;
			while (entry[*i] && entry[*i] != quote)
				(*i)++;
			if (entry[*i])
				(*i)++;
		}
		else if (entry[*i] == ' ' || is_operator(entry[*i]))
			break;
		else
			(*i)++;
	}
	return (ft_substr(entry, start, *i - start));
}

t_token	*create_token(char *val, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = val;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token * define_token(char* entry)
{
	t_token *head;
	t_token *new;
	char *token_str;
	t_token_type type;
	int i;

	head = NULL;
	i = 0 ;
	while (entry[i])
	{
		token_str = extract_token(entry, &i);
		if (!token_str || token_str[0] == '\0')
		{
			free(token_str);
			continue;
		}
		type = get_type(token_str);
		new = create_token(token_str, type);
		add_token_back(&head, new);
	}
	return (head);
}
