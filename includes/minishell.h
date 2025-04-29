/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/29 21:33:11 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include "expand.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "token.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*open*/
# include <fcntl.h>

/*signals*/
# include <signal.h>
# include <termios.h>

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

extern volatile sig_atomic_t	g_signal_value;

typedef struct s_minishell
{
	int							launch_mode;
	int							input_fd;
	char						**envp_copy;
	bool						is_running;
	t_token						*tokens;
	t_expand					*expand;

}								t_minishell;

enum							e_launch_modes
{
	TTY_MODES,
	SCRIPT_MODES,
	HERE_DOC_MODES
};

/*signals*/
typedef struct sigaction		t_sigaction;

// clean.c --->
void							free_minishell(t_minishell *minishell);
void							free_minishell(t_minishell *minishell);

// main.c --->
void							clean_error(char *error_message,
									t_minishell *minishell);
void							check_args_count(int argc, char **argv,
									t_minishell *minishell);
char							*get_entry(t_minishell *minishell);
void							clean_error(char *error_message,
									t_minishell *minishell);
void							check_args_count(int argc, char **argv,
									t_minishell *minishell);
char							*get_entry(t_minishell *minishell);

// init.c --->
void							init_minishell(t_minishell *minishell,
									char **envp);
void							copy_envp(char **envp, t_minishell *minishell);
void							init_minishell(t_minishell *minishell,
									char **envp);
void							copy_envp(char **envp, t_minishell *minishell);

// token.c --->
void							tokens(t_minishell *minishell, char *entry);
t_token							*define_token(char *line);
bool							has_closed_quotes(char *str);
void							tokens(t_minishell *minishell, char *entry);
t_token							*define_token(char *line);
bool							has_closed_quotes(char *str);

// utils_token.c --->
t_token							*create_token(char *val, t_token_type type);
void							add_token_back(t_token **list_token,
									t_token *new);
t_token							*create_token(char *val, t_token_type type);
void							add_token_back(t_token **list_token,
									t_token *new);
// bool		is_operator(char c);
char							*remove_quotes(const char *str);
void							format_tokens(t_token *tokens,
									t_minishell *minishell);

// expand.c --->
char							*expand_variable(char *str,
									t_minishell *minishell);

// utils_expand.c --->
int								is_valid_var_char(char c, int len);

// debug.c --->
void							print_tokens(t_token *tokens);

// signals.c --->
void							signal_handler(int signum);
void							print_tokens(t_token *tokens);

// signals.c --->
void							disable_control_echo(void);
void							signal_initialisation(void);
void							signal_handler(int signum);

#endif
