/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:34:11 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/07 16:53:49 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strncpy(const char *src, char *dest, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_countwords(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_clean(char **tab, int words_allocated)
{
	int	i;

	i = 0;
	while (i < words_allocated)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_filltab(const char *s, char **tab, char c)
{
	int	i;
	int	word_start;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_start = i;
			while (s[i] && s[i] != c)
				i++;
			tab[word_count] = malloc(sizeof(char) * (i - word_start + 1));
			if (!tab[word_count])
				return (ft_clean(tab, word_count));
			ft_strncpy(&s[word_start], tab[word_count], i - word_start);
			word_count++;
		}
		else
			i++;
	}
	tab[word_count] = NULL;
	return (tab);
}

// Fonction principale pour découper la chaîne en mots.
char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_countwords(s, c);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	return (ft_filltab(s, tab, c));
}
