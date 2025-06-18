/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/18 20:02:28 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->is_running = true;
	minishell->error_code = 0;
	minishell->input_fd = -1;
	minishell->output_fd = -1;
	minishell->heredoc_fd = -1;
	minishell->saved_inputfd = -1;
	minishell->saved_outputfd = -1;
	minishell->launch_mode = 0;
	minishell->errfound = false;
	minishell->cmds_count = 0;
	split_envp(minishell, envp);
}
