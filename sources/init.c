/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/24 16:35:53 by egache           ###   ########.fr       */
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

void	define_shlvl(t_denvp **list)
{
	t_denvp	*current;
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	current = (*list);
	while (current)
	{
		if (ft_strcmp("SHLVL", current->var[0]) == 0)
		{
			free(current->var[1]);
			current->var[1] = ft_strjoin("=", shlvl);
			return (free(shlvl));
		}
		current = current->next;
	}
	return (free(shlvl));
}

void	fill_envpnull(t_minishell *minishell, char *var)
{
	t_denvp	*new_denvp;
	t_denvp	*new_export;

	new_export = create_denvp(fill_variables(var));
	new_denvp = create_denvp(fill_variables(var));
	add_denvp_back(&minishell->export, new_export);
	add_denvp_back(&minishell->envp, new_denvp);
}

void	fill_envp(t_minishell *minishell, char **envp)
{
	t_denvp	*new_denvp;
	t_denvp	*new_export;
	int		i;
	char	**var1;
	char	**var2;

	i = 0;
	while (envp[i] != NULL)
	{
		var1 = fill_variables(envp[i]);
		var2 = fill_variables(envp[i]);
		new_export = create_denvp(var1);
		new_denvp = create_denvp(var2);
		add_denvp_back(&minishell->export, new_export);
		add_denvp_back(&minishell->envp, new_denvp);
		i++;
	}
	return ;
}

void	split_envp(t_minishell *minishell, char **envp)
{
	char *get_pwd;
	char *pwd_var;

	get_pwd = getcwd(NULL, 0);
	pwd_var = ft_strjoin("PWD=", get_pwd);
	if (envp[0] != NULL)
		fill_envp(minishell, envp);
	if (envp[0] == NULL || (envp[0] != NULL && getenv("SHLVL") == NULL))
	{
		fill_envpnull(minishell, pwd_var);
		fill_envpnull(minishell, "SHLVL=1");
		fill_envpnull(minishell, "_=/usr/bin/env");
	}
	if (getenv("SHLVL") != NULL)
	{
		define_shlvl(&minishell->envp);
		define_shlvl(&minishell->export);
	}
	// else
	// {
		// fill_envp(minishell, envp);
	// 	else
	// 	{
	// 		fill_envpnull(minishell, pwd_var);
	// 		fill_envpnull(minishell, "SHLVL=1");
	// 		fill_envpnull(minishell, "_=/usr/bin/env");
	// 	}
	// }
	free(get_pwd);
	return (free(pwd_var));
}
