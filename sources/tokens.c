/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:40:27 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/06 20:03:37 by egache           ###   ########.fr       */
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

t_token	*define_tokens(char *entry)
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

void	format_tokens(t_token *tokens, t_minishell *minishell)
{
	char	*cleaned;
	char	*expanded;

	while (tokens)
	{
		expanded = expand_variable(tokens->value, minishell);
		free(tokens->value);
		cleaned = remove_quotes(expanded);
		free(expanded);
		if (cleaned)
			tokens->value = cleaned;
		tokens = tokens->next;
	}
}

int	check_tokens(t_minishell *minishell, t_token *tokens)
{
	t_token	*current;
	bool	errfound;

	current = tokens;
	chainedlst_to_tab(minishell, minishell->envp);
	errfound = check_first_token(minishell, &current);
	while (current != NULL)
	{
		if (current->type != T_WORD && current->type != T_PIPE)
		{
			errfound = operator_error(minishell, current, errfound);
			if (errfound == true)
				return (1); // ON DOIT RIEN FAIRE SI ERREUR OPERATEURS
		}
		else if (current->type == T_PIPE)
			errfound = pipe_error(minishell, current, errfound);
		printf("current->value in check->tokens : %s\n", current->value);
		current = current->next;
	}
	return (0);
}

void	tokens(t_minishell *minishell, char *entry)
{
	if (has_closed_quotes(entry))
		return ;
	minishell->tokens = define_tokens(entry);
	format_tokens(minishell->tokens, minishell);
	check_tokens(minishell, minishell->tokens);
	print_tokens(minishell->tokens);
}
