/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:44:58 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/18 13:39:19 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_fd.h"

static int	ft_printptr(void *ptr, int i, int fd)
{
	unsigned long	addr;
	char			*base;

	base = "0123456789abcdef";
	if (!ptr)
		return (ft_printstr_fd("(nil)", i, fd));
	addr = (unsigned long)ptr;
	if (addr >= 16)
		i = ft_printptr((void *)(addr / 16), i, fd);
	i = ft_printchar_fd(base[addr % 16], i, fd);
	return (i);
}

static int	ft_printhex(int nbr, char format, int i, int fd)
{
	char	*nb;

	nb = ft_itoahex(nbr, format);
	i = ft_printstr_fd(nb, i, fd);
	free(nb);
	return (i);
}

static int	ft_handle_pointer(void *ptr, int i, int fd)
{
	if (!ptr)
		return (ft_printstr_fd("(nil)", i, fd));
	i = ft_printstr_fd("0x", i, fd);
	return (ft_printptr(ptr, i, fd));
}

static int	ft_handle_format(const char specifier, va_list args, int i, int fd)
{
	if (specifier == 'c')
		i = ft_printchar_fd(va_arg(args, int), i, fd);
	else if (specifier == 's')
		i = ft_printstr_fd(va_arg(args, char *), i, fd);
	else if (specifier == 'p')
		i = ft_handle_pointer(va_arg(args, void *), i, fd);
	else if (specifier == 'd' || specifier == 'i')
		i = ft_printdigital_fd(va_arg(args, int), i, fd);
	else if (specifier == 'u')
		i = ft_printudigital_fd(va_arg(args, int), i, fd);
	else if (specifier == 'x' || specifier == 'X')
		i = ft_printhex(va_arg(args, int), specifier, i, fd);
	else if (specifier == '%')
		i = ft_printchar_fd('%', i, fd);
	return (i);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = -1;
	va_start(args, format);
	while (format[++j])
	{
		if (format[j] == '%')
		{
			j++;
			i = ft_handle_format(format[j], args, i, fd);
		}
		else
			i = ft_printchar_fd(format[j], i, fd);
	}
	va_end(args);
	return (i);
}
