/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:32:30 by tsaby             #+#    #+#             */
/*   Updated: 2024/11/12 13:43:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tabjoin;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tabjoin = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tabjoin)
		return (tabjoin);
	while (s1[i])
	{
		tabjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tabjoin[i + j] = s2[j];
		j++;
	}
	tabjoin[i + j] = '\0';
	return (tabjoin);
}

/*#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*result;

	s1 = "Hello, ";
	s2 = "YO LE RAP!";
	result = ft_strjoin(s1, s2);
	if (result)
	{
		printf("Résultat de ft_strjoin : %s\n", result);
		free(result);
	{
		printf("Erreur d'allocation de mémoire\n");
	}
	return (0);
}
*/
