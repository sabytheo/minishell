/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:06:39 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/20 11:31:29 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	ft_handle_unmatched_quote(char *result, const char *str,
		int quote_start, int j)
{
	result[j] = str[quote_start];
	return (j + 1);
}

static int	ft_process_quoted_content(const char *str, int *i, char *result,
		int j, char quote_char)
{
	while (str[*i])
	{
		if (str[*i] == quote_char)
		{
			(*i)++;
			return (j);
		}
		else if ((quote_char == '"' && str[*i] == '\'') || (quote_char == '\''
				&& str[*i] == '"'))
			result[j++] = str[(*i)++];
		else
			result[j++] = str[(*i)++];
	}
	return (-1);
}

static int	ft_handle_quote_pair(const char *str, int *i, char *result, int j)
{
	char	quote_char;
	int		quote_start;
	int		new_j;

	quote_char = str[*i];
	quote_start = *i;
	(*i)++;
	new_j = ft_process_quoted_content(str, i, result, j, quote_char);
	if (new_j == -1)
		return (ft_handle_unmatched_quote(result, str, quote_start, j));
	return (new_j);
}

char	*remove_quotes(const char *str)
{
	int		i;
	int		j;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]))
			j = ft_handle_quote_pair(str, &i, result, j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
