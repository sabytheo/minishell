/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:40:27 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/01 15:40:31 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_closed_quotes(char *str, bool message)
{
	int		i;
	bool	squote;
	bool	dquote;

	i = 0;
	squote = false;
	dquote = false;
	while (str[i])
	{
		if (str[i] == '\'' && dquote == false)
			squote = !squote;
		else if (str[i] == '"' && squote == false)
			dquote = !dquote;
		i++;
	}
	if (message == true)
	{
		if (squote == true)
			ft_putendl_fd(E_UNCLOSE_SQUOTE, 2);
		else if (dquote == true)
			ft_putendl_fd(E_UNCLOSE_DQUOTE, 2);
	}
	return (squote || dquote);
}

void	define_tokens(char *entry, t_minishell *minishell)
{
	t_token			*token;
	t_token			*new;
	char			*token_str;
	t_token_type	type;
	int				i;

	token = NULL;
	i = 0;
	while (entry[i])
	{
		token_str = extract_token(entry, &i);
		if (!token_str)
			return (free_minishell(minishell, E_AFAILED, true));
		type = get_type(token_str);
		new = create_token(token_str, type);
		if (!new)
		{
			free(token_str);
			return (free_minishell(minishell, E_AFAILED, true));
		}
		add_token_back(&token, new);
	}
	minishell->tokens = token;
}

static void	cleanup_and_exit(t_minishell *minishell, char *expanded)
{
	if (expanded)
		free(expanded);
	if (minishell->expansion_map)
		free(minishell->expansion_map);
	return (free_minishell(minishell, E_AFAILED, true));
}

void	format_tokens(t_token *tokens, t_minishell *minishell)
{
	char	*cleaned;
	char	*expanded;

	while (tokens)
	{
		minishell->expansion_map = create_expansion_map(tokens->value);
		if (!minishell->expansion_map)
			return (free_minishell(minishell, E_AFAILED, true));
		expanded = expand_variable(tokens->value, minishell);
		if (!expanded)
			return (cleanup_and_exit(minishell, NULL));
		cleaned = remove_quotes(expanded);
		if (!cleaned)
			return (cleanup_and_exit(minishell, expanded));
		free(tokens->value);
		free(expanded);
		free(minishell->expansion_map);
		minishell->expansion_map = NULL;
		if (cleaned)
			tokens->value = cleaned;
		tokens = tokens->next;
	}
}

int	tokens(t_minishell *minishell, char *entry)
{
	if (has_closed_quotes(entry, true))
		return (-1);
	define_tokens(entry, minishell);
	format_tokens(minishell->tokens, minishell);
	if (check_tokens(minishell) == false)
		return (-1);
	exec_tokens(minishell);
	return (0);
}
