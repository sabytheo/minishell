/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:01:48 by tsaby             #+#    #+#             */
/*   Updated: 2024/11/22 14:05:10 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printchar(int c, int i)
{
	return (i += write(1, &c, 1));
}

int	ft_printstr(char *s, int i)
{
	if (!s)
		return (ft_printstr("(null)", i));
	while (*s)
	{
		i = ft_printchar(*s++, i);
	}
	return (i);
}

int	ft_printdigital(int nbr, int i)
{
	char	*nb;

	nb = ft_itoa(nbr);
	i = ft_printstr(nb, i);
	free(nb);
	return (i);
}

int	ft_printudigital(unsigned int nbr, int i)
{
	char	*nb;

	nb = ft_uitoa(nbr);
	i = ft_printstr(nb, i);
	free(nb);
	return (i);
}
