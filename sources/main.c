/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:34 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/18 13:50:07 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clean and exit function.
** Print error message,clean then exit.
*/
void	clean_error(char *error_message)
{
	// besoin de completer cette fonction pour tout bien clean,free.
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

/*
** check args, and define launch_mode.
** TTY_MODES, HERE_DOC_MODES and SCRIPT_MODES.
** For SCRIPT_MODES and HERE_DOC_MODES, set input_fd.
*/
void	check_args_count(int argc, char **argv, t_minishell *minishell)
{
	if (argc > 2)
		return (clean_error(E_MARGS));
	else if (argc == 2)
	{
		minishell->launch_mode = SCRIPT_MODES;
		minishell->input_fd = open(argv[1], O_RDONLY);
		if (minishell->input_fd == -1)
			return (clean_error(E_OPENFILE));
	}
	else if (argc == 1)
		minishell->launch_mode = TTY_MODES;
	else
	{
		minishell->launch_mode = HERE_DOC_MODES;
		minishell->input_fd = STDIN_FILENO;
	}
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
int	main(int argc, char **argv)
{
	char		*entry;
	t_minishell	minishell;

	minishell.input_fd = 0;
	minishell.launch_mode = 0;
	check_args_count(argc, argv, &minishell);
	// faire une fonction pour init structure.
	while (1)
	{
		entry = get_entry(&minishell);
		add_history(entry);
		free(entry);
	}
	return (0);
}
