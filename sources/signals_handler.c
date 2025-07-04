/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:12:23 by egache            #+#    #+#             */
/*   Updated: 2025/07/04 14:58:42 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	disable_control_echo();
	if (signum == SIGINT)
	{
		g_signal_value = signum;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_value = 0;
	}
	else if (signum == SIGQUIT)
	{
		g_signal_value = signum;
		rl_on_new_line();
		rl_redisplay();
		g_signal_value = 0;
	}
}

void	heredoc_signal_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_value = 1;
}

int	stop_readline(void)
{
	if (g_signal_value)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}
