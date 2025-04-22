/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:06:39 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/22 17:03:02 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_token_quotes(t_token *tokens)
{
	char *cleaned;
	while (tokens)
	{
		cleaned = remove_quotes(tokens->value);
		free(tokens->value);
		if (cleaned)
			tokens->value = cleaned;
		tokens = tokens->next;
	}
}

char *remove_quotes(const char* str)
{
	int i;
	int j;
	char quote;
	char *new;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new)
		return (NULL); // NEED FAIRE UNE FONCTION POUR FREE ET RETOURNER NULL:
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

bool	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
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
