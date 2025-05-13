/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:16:22 by egache            #+#    #+#             */
/*   Updated: 2025/05/13 15:02:37 by tsaby            ###   ########.fr       */
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
		args[i] = ft_strdup((*current)->value);
		if (args[i] == NULL)
			return (NULL); // NEED FREE ?
		(*current) = (*current)->next;
		i++;
	}
	return (args);
}

static int	*fill_type(t_token *current)
{
	int	*type;
	int	i;
	int	size;

	i = 0;
	size = get_cmds_size(current);
	type = malloc(sizeof(int) * (size + 1));
	if (type == NULL)
		return (NULL); // NEED FREE ?
	while (current != NULL && current->type != T_PIPE)
	{
		type[i] = current->type;
		current = current->next;
		i++;
	}
	return (type);
}

void	split_tokens(t_token *tokens, t_minishell *minishell)
{
	t_token	*current;
	t_cmds	*new;
	char	**args;
	int		*type;

	current = tokens;
	while (current != NULL)
	{
		type = fill_type(current);
		args = fill_args(&current);
		new = create_cmds(type, args);
		add_cmds_back(&minishell->cmds, new);
		if (current != NULL)
			current = current->next;
		else
			return ;
	}
	return ;
}

void	execute_single_command(t_minishell *minishell, t_cmds *cmds)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		// if (setup_redirection(cmds->args) < 0)
		// 	clean_error(NULL, minishell);
		if (is_a_builtins(cmds->args[0]))
			exec_builtins(minishell); // changer exec-builtins par minishell->cmd->args,
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
	t_cmds *current;

	split_tokens(minishell->tokens, minishell);
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
