/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/02 13:21:48 by tsaby            ###   ########.fr       */
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

bool	should_expand(char *str, int i)
{
	int		j;
	bool	in_squote;
	bool	in_dquote;

	if (str[i] != '$' || str[i + 1] == '\0' || !(ft_isalpha(str[i + 1]) || str[i
			+ 1] == '_' || str[i + 1] == '?'))
		return (false);
	j = 0;
	in_squote = false;
	in_dquote = false;
	while (j < i)
	{
		if (str[j] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[j] == '"' && !in_squote)
			in_dquote = !in_dquote;
		j++;
	}
	return (!in_squote);
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
