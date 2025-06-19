/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:19:44 by egache            #+#    #+#             */
/*   Updated: 2025/06/19 16:03:43 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_initialisation(void)
{
	t_sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	signal_ignore(void)
{
	t_sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = SIG_IGN;
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

/*
CTRL - C - SIGINT
Quitte l'execution en cours
Display une nouvelle ligne si aucune execution en cours

CTRL - \ - SIGQUIT

CTRL - D
Envoie un EOF a stdin
*/
