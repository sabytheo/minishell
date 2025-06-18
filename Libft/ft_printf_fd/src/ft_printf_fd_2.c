/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:01:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/18 13:39:56 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_fd.h"

int	ft_printchar_fd(int c, int i, int fd)
{
	return (i += write(fd, &c, 1));
}

int	ft_printstr_fd(char *s, int i, int fd)
{
	if (!s)
		return (ft_printstr_fd("(null)", i, fd));
	while (*s)
	{
		i = ft_printchar_fd(*s++, i, fd);
	}
	return (i);
}

int	ft_printdigital_fd(int nbr, int i, int fd)
{
	char	*nb;

	nb = ft_itoa(nbr);
	i = ft_printstr_fd(nb, i, fd);
	free(nb);
	return (i);
}

int	ft_printudigital_fd(unsigned int nbr, int i, int fd)
{
	char	*nb;

	nb = ft_uitoa(nbr);
	i = ft_printstr_fd(nb, i, fd);
	free(nb);
	return (i);
}
