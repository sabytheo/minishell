/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/05/13 17:15:51 by egache           ###   ########.fr       */
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
int	setup_redirections(t_cmds *cmds, t_minishell *minishell)
{
	int		i;
	t_cmds	*current;

	i = 0;
	current = cmds;
	while (current)
	{
		while (current->args[i])
		{
			if (current->type[i] == T_REDIR_OUT)
			{
				minishell->fd = open(current->args[i + 1], O_RDONLY);
				if (minishell->fd < 0)
					return (perror(current->args[i]), -1);
				if (dup2(minishell->fd, STDIN_FILENO) < 0)
				{
					perror("dup2");
					close(minishell->fd);
					return (-1);
				}
				close(minishell->fd);
			}
			else if (current->type[i] == T_REDIR_IN)
			{
				minishell->fd = open(current->args[i + 1],
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (minishell->fd < 0)
					return (perror(current->args[i]), -1);
				if (dup2(minishell->fd, STDOUT_FILENO) < 0)
				{
					perror("dup2");
					close(minishell->fd);
					return (-1);
				}
				close(minishell->fd);
			}
			i++;
		}
		current = current->next;
	}
	return (0);
}

void	execute_single_command(t_minishell *minishell, t_cmds *cmds)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (setup_redirections(cmds, minishell) < 0)
			printf("coucou");
		if (is_a_builtins(cmds->args[0]))
			exec_builtins(minishell);
		// changer exec-builtins par minishell->cmd->args,
		else
		{
			execve(find_path(cmds->args[0], minishell->envp_tab, 0), cmds->args,
				minishell->envp_tab);
			perror("execve");
			clean_error(NULL, minishell);
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
}

void	exec_tokens(t_minishell *minishell)
{
	t_cmds	*current;
	split_tokens(minishell->tokens, minishell);
	print_cmds(minishell->cmds);
	current = minishell->cmds;
		while (current)
		{
			// if (minishell->cmds->next != NULL)
			// 	// execute_piped_command();
			// else
			execute_single_command(minishell, current);
			current = current->next;
		}
}
