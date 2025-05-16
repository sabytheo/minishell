/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:34 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/16 15:41:59 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_value;

/*
** check args, and define launch_mode.
** TTY_MODES and SCRIPT_MODES.
** For SCRIPT_MODES , set input_fd.
*/
void	check_args_count(int argc, char **argv, t_minishell *minishell)
{
	if (argc > 2)
		return (clean_error(E_MARGS, minishell));
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
	else
	{
		entry = get_next_line(minishell->input_fd);
		if (entry == NULL)
			return (NULL);
		tmp = entry;
		entry = ft_strtrim(entry, "\n");
		free(tmp);
		return (entry);
	}
}

/*
** Main function of minishell.
** Init,check args.. (A COMPLETER)
*/

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	init_minishell(&minishell, envp);
	check_args_count(argc, argv, &minishell);
	signal_initialisation();
	chainedlst_to_tab(&minishell, minishell.envp);
	while (minishell.is_running == true)
	{
		minishell.entry = get_entry(&minishell);
		if (minishell.entry == NULL)
			break ;
		add_history(minishell.entry);
		tokens(&minishell, minishell.entry);
		// exec_builtins(&minishell);
		free_cmds(&minishell.cmds);
		free_tokens(&minishell.tokens);
		// FAIRE UNE FONCTION POUR FREE A CHAQUE APPEL
		// FAIRE UNE FONCTION POUR FREE A CHAQUE APPEL
		free(minishell.entry);
		// FAIRE UNE FONCTION POUR FREE A CHAQUE APPEL
	}
	free(minishell.envp_tab);
	free_minishell(&minishell);
	return (0);
}
