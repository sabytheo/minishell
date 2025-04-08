/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:54:05 by tsaby             #+#    #+#             */
/*   Updated: 2024/11/22 14:03:39 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_itoahex(int n, char format);
size_t	ft_strlen(const char *str);
int		ft_printudigital(unsigned int nbr, int i);
int		ft_printdigital(int nbr, int i);
int		ft_printstr(char *s, int i);
int		ft_printchar(int c, int i);
#endif
