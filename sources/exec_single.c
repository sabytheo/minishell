/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:53:58 by egache            #+#    #+#             */
/*   Updated: 2025/06/24 16:39:26 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_thechild(pid_t pid, t_minishell *minishell)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->error_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->error_code = 128 + WTERMSIG(status);
}

int	before_builtins(t_cmds *cmds, t_minishell *minishell)
{
	if (cmds->cmdfound == false)
	{
		setup_redirections(cmds->redirs, minishell, cmds->cmdfound);
		return (-1);
	}
	if (is_a_builtins(cmds->args[0]))
	{
		if (setup_redirections(cmds->redirs, minishell, cmds->cmdfound) < 0)
		{
			reset_redir(minishell);
			return (-1);
		}
		exec_builtins(minishell, cmds);
		reset_redir(minishell);
		return (-1);
	}
	return (0);
}

void	execute_single_command(t_minishell *minishell)
{
	pid_t	pid;
	t_cmds	*cmds;
	char	*path;

	cmds = minishell->cmds;
	if (prepare_heredocs(minishell, cmds) < 0)
		return ;
	if (before_builtins(cmds, minishell) < 0)
		return ;
	signal_ignore();
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (setup_redirections(cmds->redirs, minishell, cmds->cmdfound) < 0)
			exit_and_clear_child(minishell->error_code, minishell);
		if (cmds->cmdfound == true)
		{
			if (ft_strnstr(cmds->args[0], "/", ft_strlen(cmds->args[0])) != NULL)
				path = cmds->args[0];
			else
				path = find_path(cmds->args[0], minishell->envp_tab, 0);
			execve(path, cmds->args, minishell->envp_tab);
			perror("execve");
			if(ft_strncmp(cmds->args[0],"../",3) != 0)
				free(path);
			exit_and_clear_child(minishell->error_code, minishell);
		}
	}
	wait_thechild(pid, minishell);
	cleanup_heredocs(minishell);
	return ;
}
