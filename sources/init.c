/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/25 00:11:56 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void copy_envp(char **envp, t_minishell *minishell)
{
	int i;
	int size;

	if (!envp)
		return ;
	size = 0;
	while (envp[size] != NULL)
		size++;
	minishell->envp_copy = (char **)malloc((size + 1) * sizeof(char *));
	if (minishell->envp_copy == NULL)
		return(clean_error(E_MALLOC,minishell));
	i = 0;
	while(envp[i])
	{
		minishell->envp_copy[i] = ft_strdup(envp[i]);
		// printf("%s\n",minishell->envp_copy[i]);
		if (minishell->envp_copy[i] == NULL)
			return (clean_error(E_MALLOC,minishell));
		i++;
	}
	minishell->envp_copy[i] = NULL;
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	t_token * token;

	token = NULL;
	ft_bzero(minishell,sizeof(t_minishell));
	minishell->tokens = token;
	minishell->is_running = true;
	minishell->input_fd = STDIN_FILENO;
	minishell->launch_mode = 0;
	copy_envp(envp,minishell);
}
