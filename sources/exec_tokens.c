/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/05/22 17:45:08 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_args(t_token **current)
{
	char	**args;
	int		i;
	int		size;

	i = 0;
	size = get_cmds_size((*current));
	args = malloc(sizeof(char *) * (size + 1));
	if (args == NULL)
		return (NULL); // NEED FREE ?
	args[size] = NULL;
	while ((*current) != NULL && (*current)->type != T_PIPE)
	{
		if ((*current)->type >= T_REDIR_IN && (*current)->type <= T_HEREDOC)
			(*current) = (*current)->next;
		else
		{
			args[i] = ft_strdup((*current)->value);
			if (args[i] == NULL)
				return (NULL); // NEED FREE ?
			i++;
		}
		(*current) = (*current)->next;
	}
	return (args);
}

void	split_tokens(t_token *tokens, t_minishell *minishell)
{
	t_token	*current;
	t_cmds	*new;
	char	**args;

	current = tokens;
	while (current != NULL)
	{
		args = fill_args(&current);
		new = create_cmds(args);
		add_cmds_back(&minishell->cmds, new);
		if (current != NULL)
			current = current->next;
		else
			return ;
	}
	return ;
}

int	setup_redirections(t_token *tokens, t_minishell *minishell)
{
	t_token	*current;
	int errfound;

	errfound = 0;
	current = tokens;
	while (current)
	{
		// printf(" 2 fd output :%d\n", minishell->output_fd);
		if (current->type == T_REDIR_IN)
			errfound = redir_in(minishell, current);
		else if (current->type == T_REDIR_OUT)
			errfound = redir_out(minishell, current);
		else if (current->type == T_APPEND)
			errfound = redir_append(minishell, current);
		else if (current->type == T_HEREDOC)
			errfound = redir_heredoc(minishell, current);
		if (errfound < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

void	reset_redir(t_minishell *minishell)
{
	if (minishell->saved_inputfd > 2)
	{
		if (dup2(minishell->saved_inputfd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->saved_inputfd);
		}
		close(minishell->saved_inputfd);
		minishell->saved_inputfd = -1;
	}
	if (minishell->saved_outputfd > 2)
	{
		if (dup2(minishell->saved_outputfd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(minishell->saved_outputfd);
		}
		close(minishell->saved_outputfd);
		minishell->saved_outputfd = -1;
	}
}
void	execute_single_command(t_minishell *minishell, t_cmds *cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	// printf(" minishell->cmdfound %d\n", minishell->cmdfound);
	if (minishell->cmdfound == false)
	{
		setup_redirections(minishell->tokens, minishell);
		//reset_redir(minishell);
		return;
	}
	if (is_a_builtins(cmds->args[0]))
	{
		if (setup_redirections(minishell->tokens, minishell) < 0)
		{
			reset_redir(minishell);
			return ;
		}
		exec_builtins(minishell);
		reset_redir(minishell);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (setup_redirections(minishell->tokens, minishell) < 0)
			exit_and_clear_child(status,minishell);
		if (minishell->cmdfound == true)
		{
			execve(find_path(cmds->args[0], minishell->envp_tab, 0), cmds->args,
				minishell->envp_tab);
			perror("execve");
			exit_and_clear_child(status, minishell);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->error_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->error_code = 128 + WTERMSIG(status);
	}
	return ;
}

void	exec_tokens(t_minishell *minishell)
{
	t_cmds	*current;

	split_tokens(minishell->tokens, minishell);
	current = minishell->cmds;
	// print_cmds(current);
	while (current)
	{
		// if (minishell->cmds->next != NULL)
		// 	// execute_piped_command();
		// else
		execute_single_command(minishell, current);
		current = current->next;
	}
	if (minishell->saved_inputfd != -1)
	{
		close(minishell->saved_inputfd);
		minishell->saved_inputfd = -1;
	}
	if (minishell->saved_outputfd != -1)
	{
		close(minishell->saved_outputfd);
		minishell->saved_outputfd = -1;
	}
}
