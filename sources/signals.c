/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:19:44 by egache            #+#    #+#             */
/*   Updated: 2025/06/17 21:15:59 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_initialisation(void)
{
	t_sigaction	action;
	t_sigaction quit;

	sigemptyset(&action.sa_mask);
	sigemptyset(&quit.sa_mask);
	action.sa_flags = 0;
	quit.sa_flags = 0;
	action.sa_handler = signal_handler;
	quit.sa_handler = SIG_DFL;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &quit, NULL);
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
		printf("-");
		g_signal_value = signum;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_value = 0;
	}
	// else if (signum == SIGQUIT)
	// {
	// 	g_signal_value = signum;
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// 	g_signal_value = 0;
	// }
}

void	heredoc_signal_handler(int signum)
{
	(void)signum;
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

/*
CTRL - C - SIGINT
Quitte l'execution en cours
Display une nouvelle ligne si aucune execution en cours

CTRL - \ - SIGQUIT

CTRL - D
Envoie un EOF a stdin
*/
