/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:49:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/25 01:17:06 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *name, char **envp)
{
	int	i;
	size_t len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len_name) == 0
			&& envp[i][len_name] == '=')
			return (envp[i] + len_name + 1);
		i++;
	}
	return ("");
}

char	*expand_variable(char *str, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	name[256];
	char	*expand;

	i = 0;
	k = 0;
	expand = ft_calloc(4096, sizeof(char));
	while (str[i])
	{
		if (str[i] == '$' && str[i + i] && (ft_isalpha(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			i++;
			j = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				name[j++] = str[i++];
			name[j] = '\0';
			ft_strlcat(expand, get_name(name, envp), 4096);
			// /j += ft_strlen(get_name(name, envp));
		}
		else
			expand[k++] = str[i++];
	}
	return (expand);
}
