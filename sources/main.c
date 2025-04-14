/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:34 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/14 12:56:04 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_error(char *error_message)
{
	ft_putstr_fd(error_message,2);
	exit(EXIT_FAILURE);
}

void	check_args_count(int argc, char **argv, t_minishell minishell)
{
	if (argc > 2)
		return (clean_error(E_MARGS));
	else if (argc == 2)
	{
		minishell.launch_mode = SCRIPT_MODES;
		minishell.input_fd = open(argv[1],0);
		return ;
	}
	else
		minishell.launch_mode = TTY_MODES;
	return;

}

int	main(int argc, char **argv)
{
	char		*entry;
	t_minishell	minishell;

	minishell.input_fd = 0;
	minishell.launch_mode = 0;
	check_args_count(argc, argv, minishell);
	// faire une fonction pour init structure.
	while (1)
	{
		entry = readline("Minishell>");
		add_history(entry);
		free(entry);
	}
	return (0);
}
