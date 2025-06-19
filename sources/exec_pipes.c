/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 10:14:20 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/19 14:51:37 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_pipes(t_minishell *minishell, int cmd_index)
{
	if (cmd_index > 0) // Pas la première commande
	{
		if (dup2(minishell->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			minishell->error_code = -1;
			return (-1);
		}
	}
	if (cmd_index < minishell->cmds_count - 1) // Pas la dernière commande
	{
		if (dup2(minishell->pipes[cmd_index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			minishell->error_code = -1;
			return (-1);
		}
	}
	return (0);
}
void	execute_child_process(t_minishell *minishell, t_cmds *cmd,
		int cmd_index)
{
	char *path;

	if (dup_pipes(minishell, cmd_index) < 0)
		exit_and_clear_child(minishell->error_code, minishell);
	close_pipes_inchild(minishell);
	if (setup_redirections(cmd->redirs, minishell, cmd->cmdfound) < 0)
		exit_and_clear_child(minishell->error_code, minishell);
	if (cmd->cmdfound == true)
	{
		if (is_a_builtins(cmd->args[0]))
		{
			exec_builtins(minishell, cmd);
			exit_and_clear_child(minishell->error_code, minishell);
		}
		else
		{
			if (ft_strnstr(cmd->args[0],"/", ft_strlen(cmd->args[0])) != NULL)
				path = cmd->args[0];
			else
				path = find_path(cmd->args[0], minishell->envp_tab, 0);
			execve(path, cmd->args,minishell->envp_tab);
			perror("execve");
		}
	}
	exit_and_clear_child(minishell->error_code, minishell);
}

int	init_pipes_and_pids(t_minishell *minishell)
{
	int	i;

	minishell->pids = malloc(sizeof(pid_t) * minishell->cmds_count);
	minishell->pipes = malloc(sizeof(int *) * (minishell->cmds_count - 1));
	if (!minishell->pipes || !minishell->pids)
	{
		perror("malloc");
		return (-1);
	}
	i = 0;
	while (i < minishell->cmds_count - 1)
	{
		minishell->pipes[i] = malloc(sizeof(int *));
		if (pipe(minishell->pipes[i]) == -1)
		{
			perror("pipe");
			cleanup_pipes(minishell->pipes, i);
			free(minishell->pids);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	wait_allchild(t_minishell *minishell)
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

void	execute_piped_command(t_minishell *minishell, t_cmds *cmds)
{
	t_cmds	*current;
	int		i;

	current = cmds;
	getcmd_count(minishell);
	if (prepare_heredocs(minishell, cmds) < 0)
		return ;
	if (init_pipes_and_pids(minishell) < 0)
		return ;
	i = 0;
	while (i < minishell->cmds_count)
	{
		minishell->pids[i] = fork();
		if (minishell->pids[i] == 0)
		{
			execute_child_process(minishell, current, i);
			exit_and_clear_child(minishell->error_code, minishell);
		}
		current = current->next;
		i++;
	}
	close_pipes_inchild(minishell);
	wait_allchild(minishell);
	cleanup_pipes(minishell->pipes, minishell->cmds_count - 1);
	free(minishell->pids);
	cleanup_heredocs(minishell);
}
