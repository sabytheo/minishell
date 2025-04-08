/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:47:56 by tsaby             #+#    #+#             */
/*   Updated: 2024/12/13 12:54:07 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	b_zero(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "\0";
	int			bytes_read;
	char		*line;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_getdup(buffer);
	if (!line)
		return (NULL);
	while (bytes_read && ft_findchr(line) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (b_zero(buffer), free(line), NULL);
		buffer[bytes_read] = '\0';
		line = ft_getjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	ft_clean(buffer);
	if (line[0] == 0)
		return (free(line), NULL);
	return (line);
}
