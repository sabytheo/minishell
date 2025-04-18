/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:46 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/18 16:07:12 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** Clean and exit function.
** Print error message,clean then exit.
*/
void	clean_error(char *error_message, t_minishell *minishell)
{
	// besoin de completer cette fonction pour tout bien clean,free.
	ft_putstr_fd(error_message, 2);
	free_minishell(minishell);
	exit(EXIT_FAILURE);
}


void free_minishell(t_minishell *minishell)
{
	int i;

	if (!minishell)
		return;
	if (minishell->input_fd > 2)
		close(minishell->input_fd);
	if (minishell->envp_copy)
	{
		i = 0;
		while(minishell->envp_copy[i])
			free(minishell->envp_copy[i++]);
		free(minishell->envp_copy);
	}
}
