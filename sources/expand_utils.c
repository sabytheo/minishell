/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/30 16:55:02 by tsaby            ###   ########.fr       */
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

bool	should_expand(char *str, int i, t_minishell *minishell)
{
	if (str[i] == '$' && (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_'
			|| str[i + 1] == '?') && str[i + 1] != '\0'
		&& minishell->expansion_map[i] == true)
		return (true);
	else
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

static int whats_quote(char *str, int *i, bool *in_squote, bool *in_dquote)
{
    if (str[(*i)] == '\'' && !(*in_dquote))
    {
        *in_squote = !(*in_squote);
        (*i)++;
        return (-1);
    }
    else if (str[(*i)] == '"' && !(*in_squote))
    {
        *in_dquote = !(*in_dquote);
        (*i)++;
        return (-1);
    }
    return (0);
}


bool	*create_expansion_map(char *str)
{
	int		i;
	bool	*map;
	bool	in_squote;
	bool	in_dquote;
	int		j;

	in_squote = false;
	in_dquote = false;
	map = malloc(sizeof(bool) * (ft_strlen(str) + 1));
	if (!map)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if(whats_quote(str,&i,&in_squote,&in_dquote) < 0)
			continue;
		map[j] = !in_squote;
		i++;
		j++;
	}
	map[j] = false;
	return (map);
}
