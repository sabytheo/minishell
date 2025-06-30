/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:49:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/30 17:50:27 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(char *str, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && is_valid_var_char(str[*i], len))
	{
		len++;
		(*i)++;
	}
	return (ft_substr(str, start, len));
}

static char	*get_values(char *name, t_denvp *envp, t_minishell *minishell)
{
	if (!name)
		return (ft_strdup(""));
	if (ft_strncmp(name, "?", 1) == 0)
		return (ft_itoa(minishell->error_code));
	while (envp != NULL)
	{
		if (ft_strcmp(envp->var[0], name) == 0)
			return (ft_strdup(envp->var[1] + 1));
		envp = envp->next;
	}
	return (ft_strdup(""));
}

static char	*expand_variable_at_pos(char *str, int *i, t_minishell *minishell,
		t_expand *expand)
{
	char	*name;
	char	*value;

	(*i)++;
	name = extract_var_name(str, i);
	if (!name)
	{
		free(expand->expanded);
		return (NULL);
	}
	value = get_values(name, minishell->envp, minishell);
	if (!value)
	{
		free(expand->expanded);
		free(name);
		return (NULL);
	}
	expand->expanded = append_and_free(expand->expanded, value);
	free(name);
	free(value);
	if (!expand->expanded)
		return (NULL);
	return (expand->expanded);
}

static char	*handle_expand(char *str, int *i, t_minishell *minishell,
		t_expand *expand)
{
	char	*result;

	if (should_expand(str, *i, minishell) == true)
	{
		result = expand_variable_at_pos(str, i, minishell, expand);
		return (result);
	}
	else
	{
		result = append_char(expand, str[(*i)++]);
		return (result);
	}
}

char	*expand_variable(char *str, t_minishell *minishell)
{
	int			i;
	t_expand	expand;

	i = 0;
	expand.expanded = ft_strdup("");
	if (!expand.expanded)
		return (NULL);
	while (str[i])
	{
		expand.expanded = handle_expand(str, &i, minishell, &expand);
		if (!expand.expanded)
		{
			free(expand.expanded);
			return (NULL);
		}
	}
	return (expand.expanded);
}
