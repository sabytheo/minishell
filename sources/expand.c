/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:49:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/27 14:47:33 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_and_free(char *base, char *addition)
{
	char	*new;

	if (!base || !addition)
		return (NULL);
	new = ft_strjoin(base, addition);
	free(base);
	return (new);
}

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
	size_t	len;

	if (!name)
		return (ft_strdup(""));
	if (ft_strncmp(name, "?", 1) == 0)
		return (ft_itoa(minishell->error_code));
	len = ft_strlen(name);
	while (envp != NULL)
	{
		if (ft_strcmp(envp->var[0], name) == 0)
			return (ft_strdup(envp->var[1] + 1));
		envp = envp->next;
	}
	return (ft_strdup(""));
}

static char	*handle_expand(char *str, int *i, t_minishell *minishell,
		t_expand *expand)
{
	char	*name;
	char	*value;
	char	tmp[2];

	if (str[*i] == '$' && str[*i + 1] && expand->in_squote == false)
	{
		(*i)++;
		name = extract_var_name(str, i);
		value = get_values(name, minishell->envp, minishell);
		expand->expanded = append_and_free(expand->expanded, value);
		free(name);
		free(value);
	}
	else
	{
		tmp[0] = str[*i];
		tmp[1] = '\0';
		expand->expanded = append_and_free(expand->expanded, tmp);
		(*i)++;
	}
	return (expand->expanded);
}

char	*expand_variable(char *str, t_minishell *minishell)
{
	int			i;
	t_expand	expand;

	i = 0;
	expand.in_squote = false;
	expand.in_dquote = false;
	expand.expanded = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && expand.in_dquote == false)
			expand.in_squote = !expand.in_squote;
		else if (str[i] == '"' && expand.in_squote == false)
			expand.in_dquote = !expand.in_dquote;
		expand.expanded = handle_expand(str, &i, minishell, &expand);
	}
	return (expand.expanded);
}
