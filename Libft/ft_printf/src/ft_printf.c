/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:44:58 by tsaby             #+#    #+#             */
/*   Updated: 2024/12/01 15:52:45 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_printptr(void *ptr, int i)
{
	unsigned long	addr;
	char			*base;

	base = "0123456789abcdef";
	if (!ptr)
		return (ft_printstr("(nil)", i));
	addr = (unsigned long)ptr;
	if (addr >= 16)
		i = ft_printptr((void *)(addr / 16), i);
	i = ft_printchar(base[addr % 16], i);
	return (i);
}

static int	ft_printhex(int nbr, char format, int i)
{
	char	*nb;

	nb = ft_itoahex(nbr, format);
	i = ft_printstr(nb, i);
	free(nb);
	return (i);
}

static int	ft_handle_pointer(void *ptr, int i)
{
	if (!ptr)
		return (ft_printstr("(nil)", i));
	i = ft_printstr("0x", i);
	return (ft_printptr(ptr, i));
}

static int	ft_handle_format(const char specifier, va_list args, int i)
{
	if (specifier == 'c')
		i = ft_printchar(va_arg(args, int), i);
	else if (specifier == 's')
		i = ft_printstr(va_arg(args, char *), i);
	else if (specifier == 'p')
		i = ft_handle_pointer(va_arg(args, void *), i);
	else if (specifier == 'd' || specifier == 'i')
		i = ft_printdigital(va_arg(args, int), i);
	else if (specifier == 'u')
		i = ft_printudigital(va_arg(args, int), i);
	else if (specifier == 'x' || specifier == 'X')
		i = ft_printhex(va_arg(args, int), specifier, i);
	else if (specifier == '%')
		i = ft_printchar('%', i);
	return (i);
}

int	ft_printf(const char *format, ...)
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
			i = ft_handle_format(format[j], args, i);
		}
		else
			i = ft_printchar(format[j], i);
	}
	va_end(args);
	return (i);
}

// #include <limits.h>
// #include <stdio.h>

// int main(void)
// {
// int num;

// int original, custom;
// // Basic string tests
// printf("\n=== String Tests ===\n");
// original = printf("Original: Hello %s!\n", "World");
// custom = ft_printf("Custom  : Hello %s!\n", "World");
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Integer tests
// printf("\n=== Integer Tests %%d ===\n");
// original = printf("Original: %d, %d\n", 42, -42);
// custom = ft_printf("Custom  : %d, %d\n", 42, -42);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Integer tests 2
// printf("\n=== Integer Tests %%i ===\n");
// original = printf("Original: %i, %i\n", 42, -42);
// custom = ft_printf("Custom  : %i, %i\n", 42, -42);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Unsigned tests
// printf("\n=== Unsigned Tests ===\n");
// original = printf("Original: %u\n", UINT_MAX);
// custom = ft_printf("Custom  : %u\n", UINT_MAX);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Hex tests
// printf("\n=== Hex Tests ===\n");
// original = printf("Original: %x %X\n", 255, 255);
// custom = ft_printf("Custom  : %x %X\n", 255, 255);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Pointer tests
// num = 42;
// printf("\n=== Pointer Tests ===\n");
// original = printf("Original: %p\n", (void *)&num);
// custom = ft_printf("Custom  : %p\n", (void *)&num);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Char tests
// printf("\n=== Char Tests ===\n");
// original = printf("Original: %c%c%c\n", 'a', '\t', 'b');
// custom = ft_printf("Custom  : %c%c%c\n", 'a', '\t', 'b');
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Edge case: null string
// printf("\n=== Edge Case: NULL string ===\n");
// original = printf("Original: %s\n", (char *)NULL);
// custom = ft_printf("Custom  : %s\n", (char *)NULL);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Edge case: null pointer
// printf("\n=== Edge Case: NULL pointer ===\n");
// original = printf("Original: %p\n", (void *)NULL);
// custom = ft_printf("Custom  : %p\n", (void *)NULL);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Edge case: percent sign
// printf("\n=== Edge Cases: percent sign ===\n");
// original = printf("Original: %%\n");
// custom = ft_printf("Custom  : %%\n");
// printf("Length check: original=%d, custom=%d\n", original, custom);
// // Edge case: INT_MIN
// printf("\n=== Edge Cases: INT_MIN ===\n");
// original = printf("Original: %d %s\n", INT_MIN, (char *)NULL);
// custom = ft_printf("Custom  : %d %s\n", INT_MIN, NULL);
// printf("Length check: original=%d, custom=%d\n", original, custom);
// return (0);
// }
