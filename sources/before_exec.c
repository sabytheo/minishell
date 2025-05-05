/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:27:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/05 18:14:51 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_a_builtins(char *cmd)
{
	int len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd,"cd",len) == 0 && len == 2)
		return (true);
	if (ft_strncmp(cmd,"echo",len) == 0 && len == 4)
		return (true);
	if (ft_strncmp(cmd,"env",len) == 0 && len == 3)
		return (true);
	if (ft_strncmp(cmd,"exit",len) == 0 && len == 4)
		return (true);
	if (ft_strncmp(cmd,"export",len) == 0 && len == 6)
		return (true);
	if (ft_strncmp(cmd,"pwd",len) == 0 && len == 3)
		return (true);
	if (ft_strncmp(cmd,"unset",len) == 0 && len == 5)
		return (true);
	return (false);
	}

bool is_valid_cmd(char *cmd, t_minishell *minishell)
{
	char *path;

	if (is_a_builtins(cmd))
		return (true);
	path = find_path(cmd, minishell->envp_tab,0);
	if(path != NULL)
	{
		free(path);
		return (true);
	}
	free(path);
	return (false);
}

static int one_tokens(t_minishell *minishell, t_token *current)
{
	if (current->next != NULL)
		return (0);
	if (current->type == T_WORD)
	{
			if (is_valid_cmd(current->value,minishell))
				return (1);
			printf("Minishell: %s: command not found\n",current->value);
			minishell->error_code = 127 ;
			return(1);
	}
	else if (current->type == T_PIPE)
	{
			printf("Minishell: syntax error near unexpected token `%s'\n",current->value);
			minishell->error_code = 2 ;
			return(1);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		minishell->error_code = 2 ;
		return(1);
	}
	return (0);
}

int check_before_exec(t_minishell *minishell, t_token *tokens)
{
	t_token *current;

	current = tokens;
	chainedlst_to_tab(minishell,minishell->envp);
	if (one_tokens(minishell,current) > 0)
		return (1);
	while (current)
	{
		if (current->next && current->type != T_WORD && current->next->type != T_WORD)
			printf("Minishell: syntax error near unexpected token `%s'\n",current->next->value);
		current = current->next;
	}
	return (minishell->error_code);
}
