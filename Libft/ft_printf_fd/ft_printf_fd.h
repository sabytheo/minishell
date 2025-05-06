/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:54:05 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/06 14:03:48 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf_fd(int fd, const char *format, ...);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_itoahex(int n, char format);
size_t	ft_strlen(const char *str);
int		ft_printudigital_fd(unsigned int nbr, int i, int fd);
int		ft_printdigital_fd(int nbr, int i, int fd);
int		ft_printstr_fd(char *s, int i, int fd);
int		ft_printchar_fd(int c, int i, int fd);
#endif
