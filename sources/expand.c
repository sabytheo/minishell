/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:49:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/14 15:53:49 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_values(char *name, t_denvp *envp, t_minishell *minishell)
{
	if (!name)
		return (ft_strdup(""));
	if (ft_strncmp(name, "?", 1) == 0)
		return (ft_itoa(minishell->error_code));
	while (envp != NULL)
	{
		if (ft_strcmp(envp->var[0], name) == 0)
		{
			return (ft_strdup(envp->var[1] + 1));
		}
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

static char	*process_char(char *str, int *i, t_minishell *minishell,
		t_expand *expand)
{
	if (str[*i] == '\'' && !expand->in_dquote)
	{
		expand->in_squote = !expand->in_squote;
		(*i)++;
	}
	else if (str[*i] == '"' && !expand->in_squote)
	{
		expand->in_dquote = !expand->in_dquote;
		(*i)++;
	}
	else if (str[*i] == '$' && !expand->in_squote && str[*i + 1]
		&& (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_'
			|| str[*i + 1] == '?'))
	{
		if (!expand_variable_at_pos(str, i, minishell, expand))
			return (NULL);
	}
	else
	{
		if (!append_char(expand, str[*i]))
			return (NULL);
		(*i)++;
	}
	return (expand->expanded);
}

static char	*do_expansion(char *str, t_minishell *minishell)
{
	int			i;
	t_expand	expand;

	i = 0;
	expand.expanded = ft_strdup("");
	expand.in_squote = false;
	expand.in_dquote = false;
	if (!expand.expanded)
		return (NULL);
	while (str[i])
	{
		if (!process_char(str, &i, minishell, &expand))
		{
			free(expand.expanded);
			return (NULL);
		}
	}
	return (expand.expanded);
}

char	*expand_variable(char *str, t_minishell *minishell)
{
	if (!str)
		return (NULL);
	if (!needs_expansion(str))
	{
		minishell->expanded = false;
		return (ft_strdup(str));
	}
	minishell->expanded = true;
	return (do_expansion(str, minishell));
}
