/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:06:07 by tsaby             #+#    #+#             */
/*   Updated: 2024/11/12 16:29:55 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*chardest;
	const char	*charsrc;

	i = 0;
	chardest = (char *)dest;
	charsrc = (const char *)src;
	if (!chardest && !charsrc)
		return (NULL);
	while (i < n)
	{
		chardest[i] = charsrc[i];
		i++;
	}
	return (dest);
}
