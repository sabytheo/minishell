/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:33:49 by tsaby             #+#    #+#             */
/*   Updated: 2024/11/14 16:03:08 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		else
			i++;
	}
	return (-1);
}

static size_t	ft_strend(char const *s1, char const *set, size_t start)
{
	size_t	end;

	end = ft_strlen(s1);
	while (end > start)
	{
		if (ft_strcmp(set, s1[end - 1]) == -1)
			return (end);
		end--;
	}
	return (end);
}

static size_t	ft_strstart(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start])
	{
		if (ft_strcmp(set, s1[start]) == -1)
			return (start);
		start++;
	}
	return (start);
}

static char	*ft_strldup(char const *s1, size_t len)
{
	char	*trim;
	size_t	i;

	trim = malloc(sizeof(char) * (len + 1));
	if (trim == NULL)
		return (trim);
	i = 0;
	while (i < len)
	{
		trim[i] = s1[i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = ft_strstart(s1, set);
	end = ft_strend(s1, set, start);
	trim = ft_strldup(&((char *)s1)[start], end - start);
	return (trim);
}
