/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:46 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/30 12:38:53 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clean and exit function.
** Print error message,clean then exit.
*/
static void	free_envp(t_envp **envp)
{
	t_envp	*current;
	t_envp	*next;

	if (!envp || !*envp)
		return ;
	current = *envp;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	clean_error(char *error_message, t_minishell *minishell)
{
	// besoin de completer cette fonction pour tout bien clean,free.
	ft_putstr_fd(error_message, 2);
	free_minishell(minishell);
	exit(EXIT_FAILURE);
}

void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->envp)
		free_envp(&minishell->envp);
	rl_clear_history();
	if (minishell->input_fd > 2)
		close(minishell->input_fd);
}
