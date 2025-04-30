/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:19:44 by egache            #+#    #+#             */
/*   Updated: 2025/04/30 13:55:29 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_initialisation(void)
{
	t_sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_handler = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	disable_control_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

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
	}
	else if (signum == SIGQUIT)
	{
		g_signal_value = signum;
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
CTRL - C - SIGINT
Quitte l'execution en cours
Display une nouvelle ligne si aucune execution en cours

CTRL - \ - SIGQUIT

CTRL - D
Envoie un EOF a stdin
*/
