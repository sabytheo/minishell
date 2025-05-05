/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/05 16:08:38 by tsaby            ###   ########.fr       */
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

typedef struct s_envp
{
	char						*value;
	struct s_envp				*next;
}								t_envp;

typedef struct s_minishell
{
	int							launch_mode;
	int							input_fd;
	int							error_code;
	char						**envp_tab;
	int							envp_countline;
	bool						is_running;
	t_token						*tokens;
	t_expand					*expand;
	t_envp						*envp;

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
void							free_tokens(t_token **tokens);
void							free_tab(char **tab);

// main.c --->
void							clean_error(char *error_message,
									t_minishell *minishell);
void							check_args_count(int argc, char **argv,
									t_minishell *minishell);
char							*get_entry(t_minishell *minishell);

// init.c --->
void							init_minishell(t_minishell *minishell,
									char **envp);
void							copy_envp(char **envp, t_minishell *minishell);
void							copy_envp_bis(char **envp,
									t_minishell *minishell);

// token.c --->
void							tokens(t_minishell *minishell, char *entry);
t_token							*define_token(char *line);

// utils_token.c --->
t_token							*create_token(char *val, t_token_type type);
void							add_token_back(t_token **list_token,
									t_token *new);
bool							has_closed_quotes(char *str);
// bool		is_operator(char c);
char							*remove_quotes(const char *str);
void							format_tokens(t_token *tokens,
									t_minishell *minishell);

// expand.c --->
char							*expand_variable(char *str,
									t_minishell *minishell);

// utils_expand.c --->
int								is_valid_var_char(char c, int len);
void							chainedlst_to_tab(t_minishell *minishell,
									t_envp *envp);
int								envp_size(t_envp *envp);

// debug.c --->
void							print_tokens(t_token *tokens);
void							print_envp(t_envp *envp);

// signals.c --->
void							signal_handler(int signum);

// signals.c --->
void							disable_control_echo(void);
void							signal_initialisation(void);
void							signal_handler(int signum);

// builtins.c --->
char							*ft_echo(t_token *tokens);

// before_exec.c --->
int								check_before_exec(t_minishell *minishell,
									t_token *tokens);

// exec.c --->
char							*find_path(char *arg, char **envp, int i);

#endif
