/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:34 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/19 17:17:58 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** check args, and define launch_mode.
** TTY_MODES and SCRIPT_MODES.
** For SCRIPT_MODES , set input_fd.
*/
void	check_args_count(int argc, char **argv, t_minishell *minishell)
{
	if (argc > 2)
		return (clean_error(E_MARGS,minishell));
	else if (argc == 2)
	{
		minishell->launch_mode = SCRIPT_MODES;
		minishell->input_fd = open(argv[1], O_RDONLY);
		if (minishell->input_fd == -1)
			return (clean_error(E_OPENFILE, minishell));
	}
	else if (argc == 1)
		minishell->launch_mode = TTY_MODES;

	return ;
}

/*
** Use readline for TTY_MODES.
** Use get_next_line for HERE_DOC_MODES and SCRIPT_MODES.
**  For gnl, need to trim "\n" before return.
*/
char	*get_entry(t_minishell *minishell)
{
	char	*entry;
	char	*tmp;

	if (minishell->launch_mode == TTY_MODES)
	{
		entry = readline("Minishell>");
		entry = ft_strtrim(entry, " \t\n");
		return (entry);
	}
	entry = get_next_line(minishell->input_fd);
	if (!entry)
		return (entry);
	tmp = entry;
	entry = ft_strtrim(entry, "\n");
	free(tmp);
	return (entry);
}

/*
** Main function of minishell.
** Init,check args.. (A COMPLETER)
*/
int	main(int argc, char **argv,char **envp)
{
	char		*entry;
	t_minishell	minishell;
	t_token * token;

	init_minishell(&minishell,envp);
	check_args_count(argc, argv, &minishell);
	while (minishell.is_running)
	{
		entry = get_entry(&minishell);
		add_history(entry);
		token = define_token(entry);
		while (token)
		{
			printf("Token: %-15s | Type: %d\n", token->value, token->type);
			token = token->next;
		}

		free(entry);
	}
	free_minishell(&minishell);
	return (0);
}
