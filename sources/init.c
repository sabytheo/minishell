/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:02 by tsaby             #+#    #+#             */
/*   Updated: 2025/07/03 14:37:31 by egache           ###   ########.fr       */
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
	minishell->h_fd = -1;
	minishell->saved_inputfd = -1;
	minishell->saved_outputfd = -1;
	minishell->launch_mode = 0;
	minishell->cmds_count = 0;
	split_envp(minishell, envp);
	chainedlst_to_tab(minishell);
	signal_initialisation();
}

static int	handle_empty_env(t_minishell *minishell, char *pwd_var)
{
	if (fill_envpnull(minishell, pwd_var) < 0 || fill_envpnull(minishell,
			"SHLVL=1") < 0 || fill_envpnull(minishell, "_=/usr/bin/env") < 0)
		return (-1);
	return (0);
}

static int	handle_shlvl(t_minishell *minishell)
{
	if (define_shlvl(&minishell->envp) < 0
		|| define_shlvl(&minishell->export) < 0)
		return (-1);
	return (0);
}

static void	cleanup_and_exit(t_minishell *minishell, char *get_pwd,
		char *pwd_var)
{
	free(get_pwd);
	free(pwd_var);
	return (free_minishell(minishell, E_AFAILED, true));
}

void	split_envp(t_minishell *minishell, char **envp)
{
	char	*get_pwd;
	char	*pwd_var;

	get_pwd = getcwd(NULL, 0);
	if (!get_pwd)
		return (free_minishell(minishell, E_AFAILED, true));
	pwd_var = ft_strjoin("PWD=", get_pwd);
	if (!pwd_var)
	{
		free(get_pwd);
		return (free_minishell(minishell, E_AFAILED, true));
	}
	if (envp[0] != NULL && fill_envp(minishell, envp) < 0)
		return (cleanup_and_exit(minishell, get_pwd, pwd_var));
	if ((envp[0] == NULL || (envp[0] != NULL && getenv("SHLVL") == NULL))
		&& handle_empty_env(minishell, pwd_var) < 0)
		return (cleanup_and_exit(minishell, get_pwd, pwd_var));
	if (getenv("SHLVL") != NULL && handle_shlvl(minishell) < 0)
		return (cleanup_and_exit(minishell, get_pwd, pwd_var));
	free(get_pwd);
	free(pwd_var);
}
