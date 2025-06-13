/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/06/13 13:44:49 by tsaby            ###   ########.fr       */
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
t_token	*extract_redirections(t_token **current, t_token *redir_head)
{
	t_token	*redir_tail;
	t_token	*redir_token;
	t_token	*file_token;

	redir_tail = NULL;
	while (*current && (*current)->type != T_PIPE)
	{
		if ((*current)->type >= T_REDIR_IN && (*current)->type <= T_HEREDOC)
		{
			redir_token = *current;
			*current = (*current)->next;
			file_token = *current;
			*current = file_token->next;
			redir_token->next = file_token;
			file_token->next = NULL;
			if (!redir_head)
				redir_head = redir_token;
			else
				redir_tail->next = redir_token;
			redir_tail = file_token;
		}
		else
			(*current) = (*current)->next;
	}
	return (redir_head);
}

void	split_tokens(t_minishell *minishell)
{
	t_token	*current_args;
	t_token	*redir_head;
	t_token	*current_redir;
	t_cmds	*new;
	char	**args;

	redir_head = NULL;
	current_args = minishell->tokens;
	current_redir = minishell->tokens;
	while (current_args && current_redir)
	{
		args = fill_args(&current_args);
		new = create_cmds(args);
		new->redirs = extract_redirections(&current_redir, redir_head);
		if (args[0] != NULL)
			new->cmdfound = check_cmd(minishell, args[0]);
		add_cmds_back(&minishell->cmds, new);
		if (current_args != NULL)
			current_args = current_args->next;
		if (current_redir != NULL)
			current_redir = current_redir->next;
		else
			return ;
	}
	return ;
}

int	setup_redirections(t_token *current, t_minishell *minishell, bool cmdfound)
{
	int	errfound;

	errfound = 0;
	while (current)
	{
		if (current->type == T_REDIR_IN || current->type == T_HEREDOC)
			errfound = redir_in(minishell, current, cmdfound);
		else if (current->type == T_REDIR_OUT)
			errfound = redir_out(minishell, current, cmdfound);
		else if (current->type == T_APPEND)
			errfound = redir_append(minishell, current, cmdfound);
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
	if (prepare_heredocs(minishell,cmds) < 0)
		return ;
	if (before_builtins(cmds, minishell) < 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (setup_redirections(cmds->redirs, minishell, cmds->cmdfound) < 0)
			exit_and_clear_child(minishell->error_code, minishell);
		if (cmds->cmdfound == true)
		{
			if (ft_strnstr(cmds->args[0],"/", ft_strlen(cmds->args[0])) != NULL)
				path = cmds->args[0];
			else
				path = find_path(cmds->args[0], minishell->envp_tab, 0);
			execve(path, cmds->args, minishell->envp_tab);
			perror("execve");
			exit_and_clear_child(minishell->error_code, minishell);
		}
	}
	wait_thechild(pid, minishell);
	cleanup_heredocs(minishell);
	return ;
}

void	exec_tokens(t_minishell *minishell)
{
	t_cmds	*current;

	split_tokens(minishell);
	//print_cmds(minishell->cmds);
	current = minishell->cmds;
	if (current->next == NULL)
		execute_single_command(minishell);
	else
		execute_piped_command(minishell, current);
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
