/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/14 13:21:54 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c, int len)
{
	if (len == 0)
		return (ft_isalpha(c) || c == '_' || c == '?');
	return (ft_isalnum(c) || c == '_');
}

char	*append_char(t_expand *expand, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	expand->expanded = append_and_free(expand->expanded, tmp);
	if (!expand->expanded)
		return (NULL);
	return (expand->expanded);
}

bool	needs_expansion(char *str)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '$' && !in_single_quotes && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
			return (true);
		i++;
	}
	return (false);
}

char	*append_and_free(char *base, char *addition)
{
	char	*new;

	if (!base || !addition)
		return (NULL);
	new = ft_strjoin(base, addition);
	if (!new)
	{
		free(base);
		return (NULL);
	}
	free(base);
	return (new);
}

char	*extract_var_name(char *str, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && is_valid_var_char(str[*i], len))
	{
		len++;
		(*i)++;
	}
	return (ft_substr(str, start, len));
}
