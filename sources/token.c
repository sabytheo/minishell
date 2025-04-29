/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:42:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/29 10:37:37 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_closed_quotes(char *str)
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
	if (squote == true)
		ft_putendl_fd("minishell : syntax error : unclosed single quote ", 2);
	else if (dquote == true)
		ft_putendl_fd("minishell : syntax error : unclosed double quote ", 2);
	return (squote || dquote);
}

static t_token_type	get_type(char *str)
{
	if (!str)
		return (T_WORD);
	if (ft_strncmp(str, "|", 2) == 0)
		return (T_PIPE);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (T_APPEND);
	if (ft_strncmp(str, "<", 2) == 0)
		return (T_REDIR_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (T_REDIR_OUT);
	return (T_WORD);
}
void	explore_token(char *entry, int *i)
{
	char	quote;

	while (entry[*i])
	{
		if (entry[*i] == '\'' || entry[*i] == '"')
		{
			quote = entry[*i];
			(*i)++;
			while (entry[*i] && entry[*i] != quote)
				(*i)++;
			if (entry[*i])
				(*i)++;
		}
		else if (entry[*i] == ' ' || (entry[*i] == '|' || entry[*i] == '<'
				|| entry[*i] == '>'))
			break ;
		else
			(*i)++;
	}
	return ;
}
static char	*extract_token(char *entry, int *i)
{
	int	start;

	while (entry[*i] && entry[*i] == ' ')
		(*i)++;
	if (entry[*i] == '|' || entry[*i] == '<' || entry[*i] == '>')
	{
		start = *i;
		if ((entry[*i] == '<' || entry[*i] == '>') && entry[*i] == entry[*i + 1])
		{
			*i += 2;
			return (ft_substr(entry, start, 2));
		}
		*i += 1;
		return (ft_substr(entry, start, 1));
	}
	start = *i;
	explore_token(entry, i);
	return (ft_substr(entry, start, *i - start));
}

t_token	*define_token(char *entry)
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
		if (!token_str || token_str[0] == '\0')
		{
			free(token_str);
			continue ;
		}
		type = get_type(token_str);
		new = create_token(token_str, type);
		add_token_back(&token, new);
	}
	return (token);
}

void	tokens(t_minishell *minishell, char *entry)
{
	if (has_closed_quotes(entry))
		return ;
	minishell->tokens = define_token(entry);
	format_tokens(minishell->tokens,minishell);
	print_tokens(minishell->tokens);
}
