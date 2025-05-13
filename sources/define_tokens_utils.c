/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:04:02 by egache            #+#    #+#             */
/*   Updated: 2025/05/13 16:04:44 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	explore_token(char *entry, int *i)
{
	char	quote;

	while (entry[*i])
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
		else if (entry[*i] == ' ' || (entry[*i] == '|' || entry[*i] == '<'
				|| entry[*i] == '>'))
			break ;
		else
			(*i)++;
	}
	return ;
}

char	*extract_token(char *entry, int *i)
{
	int	start;

	while (entry[*i] && entry[*i] == ' ')
		(*i)++;
	if (entry[*i] == '|' || entry[*i] == '<' || entry[*i] == '>')
	{
		start = *i;
		if ((entry[*i] == '<' || entry[*i] == '>')
			&& entry[*i] == entry[*i + 1])
		{
			*i += 2;
			return (ft_substr(entry, start, 2));
		}
		*i += 1;
		return (ft_substr(entry, start, 1));
	}
	start = *i;
	explore_token(entry, i);
	return (ft_substr(entry, start, *i - start));
}

t_token_type	get_type(char *str)
{
	if (!str)
		return (T_WORD);
	if (ft_strncmp(str, "|", 2) == 0)
		return (T_PIPE);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (T_APPEND);
	if (ft_strncmp(str, ">", 2) == 0)
		return (T_REDIR_IN);
	if (ft_strncmp(str, "<", 2) == 0)
		return (T_REDIR_OUT);
	return (T_WORD);
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

void	add_token_back(t_token **list_token, t_token *new)
{
	t_token	*tmp;

	if (!*list_token)
	{
		*list_token = new;
		return ;
	}
	tmp = *list_token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
