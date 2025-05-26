/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:42:30 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/26 15:00:30 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("---Token: %-15s est de type: %d---\n", tokens->value,
			tokens->type);
		tokens = tokens->next;
	}
}

void	print_redirs(t_token *redirs)
{
	int		i;
	t_token	*current;

	i = 0;
	current = redirs;
	if (!redirs)
	{
		printf("  No redirections.\n");
		return ;
	}
	while (current)
	{
		printf("  Redir %d: type=%d, value=(%s)\n", i, current->type,
			current->value);
		current = current->next;
		i++;
	}
}

void	print_cmds(t_cmds *cmds)
{
	int	i;

	while (cmds)
	{
		printf("---- NEW NODE ----\n");
		if (!cmds->args)
			printf("No args in this node.\n");
		else
		{
			i = 0;
			while (cmds->args[i] != NULL)
			{
				printf("args[%d] : (%s)\n", i, cmds->args[i]);
				i++;
			}
		}
		printf("Redirections:\n");
		print_redirs(cmds->redirs);
		printf("Cmdfound:\n 0 pour false\n 1 pour true\n");
		printf("cmdfound: (%d)\n", cmds->cmdfound);
		printf("------------------\n");
		cmds = cmds->next;
	}
}

void	print_envp(t_envp *envp)
{
	while (envp)
	{
		printf("envp: %s\n", envp->value);
		envp = envp->next;
	}
}
