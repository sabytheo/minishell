/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:15:23 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/08 11:06:02 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getcmd_count(t_minishell *minishell)
{
	t_cmds	*current;
	int		size;

	current = minishell->cmds;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	if (size > 500)
	{
		ft_printf_fd(2, E_TMANYCMDS);
		return (-1);
	}
	minishell->cmds_count = size;
	return (0);
}

void	cleanup_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

void	close_pipes_inchild(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->cmds_count - 1)
	{
		close(minishell->pipes[i][0]);
		close(minishell->pipes[i][1]);
		i++;
	}
}

static void	wait_allchild(t_minishell *minishell)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < minishell->cmds_count)
	{
		waitpid(minishell->pids[i], &status, 0);
		if (i == minishell->cmds_count - 1)
		{
			if (WIFEXITED(status))
				minishell->error_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				minishell->error_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void clean_and_close(t_minishell *minishell)
{
	cleanup_pipes(minishell->pipes, minishell->cmds_count - 1);
	wait_allchild(minishell);
	free(minishell->pids);
	minishell->pids = NULL;
	cleanup_heredocs(minishell);
}
