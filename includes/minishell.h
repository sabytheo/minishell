/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:45:12 by egache            #+#    #+#             */
/*   Updated: 2025/05/26 19:33:37 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include "expand.h"
# include "ft_printf.h"
# include "ft_printf_fd.h"
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
# include <sys/wait.h>
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

typedef struct s_denvp
{
	char						**var;
	struct s_denvp				*next;
}								t_denvp;

typedef struct s_minishell
{
	int							launch_mode;
	int							input_fd;
	int							output_fd;
	int							saved_inputfd;
	int							saved_outputfd;
	int							heredoc_fd;
	int							error_code;
	char						*error_item;
	char						**envp_tab;
	int							envp_countline;
	int							fd;
	bool						is_running;
	bool						errfound;
	bool						cmdfound;
	char						*entry;
	t_token						*tokens;
	t_expand					*expand;
	t_envp						*envp;
	t_denvp						*denvp;
	t_denvp						*export;
	t_cmds						*cmds;

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
void							free_cmds(t_cmds **cmds);
void							free_envp(t_envp **envp);
void							free_denvp(t_denvp **denvp);
int								exit_and_clear_child(int error_code,
									t_minishell *minishell);

// main.c --->
void							clean_error(char *error_message,
									t_minishell *minishell);
void							check_args_count(int argc, char **argv,
									t_minishell *minishell);
char							*get_entry(t_minishell *minishell);

// init.c --->
void							init_minishell(t_minishell *minishell,
									char **envp);
void							split_envp(t_minishell *minishell, char **envp);
t_envp							*create_node(char *val);
void							add_node_back(t_envp **list_envp, t_envp *new);

// tokens.c --->
bool							has_closed_quotes(char *str);
t_token							*define_tokens(char *line);
void							format_tokens(t_token *tokens,
									t_minishell *minishell);
void							tokens(t_minishell *minishell, char *entry);

// format_tokens_utils.c --->
char							*remove_quotes(const char *str);

// check_tokens.c --->
void							check_tokens(t_minishell *minishell);
int								check_cmd(t_minishell *minishell);
char							*check_syntax(t_minishell *minishell);

// check_tokens_utils.c
bool							is_a_builtins(char *cmd);
bool							is_valid_cmd(char *cmd, t_minishell *minishell);

// define_tokens_utils.c
char							*extract_token(char *entry, int *i);
t_token_type					get_type(char *str);
t_token							*create_token(char *val, t_token_type type);
void							add_token_back(t_token **list_token,
									t_token *new);

// expand.c --->
char							*expand_variable(char *str,
									t_minishell *minishell);

// utils_expand.c --->
int								is_valid_var_char(char c, int len);
void							chainedlst_to_tab(t_minishell *minishell);
int								envp_size(t_denvp *denvp);

// debug.c --->
void							print_tokens(t_token *tokens);
void							print_envp(t_envp *envp);
void							print_cmds(t_cmds *cmds);

// signals.c --->
void							disable_control_echo(void);
void							signal_initialisation(void);
void							signal_handler(int signum);

// builtins.c --->
void							ft_echo(t_minishell *minishell, t_cmds **cmds);
void							ft_cd(t_minishell *minishell, t_cmds **cmds);
void							ft_pwd(void);
void							ft_env(t_minishell *minishell);
void							ft_export(t_minishell *minishell);
void							ft_unset(t_minishell *minishell);

// ft_export.c --->
int								ft_strcmp(const char *s1, const char *s2);

// exec.c --->
char							*find_path(char *arg, char **envp, int i);
int								exec_builtins(t_minishell *minishell);
void							exec_tokens(t_minishell *minishell);

// exec_tokens.c --->

void							split_tokens(t_token *tokens,
									t_minishell *minishell);

// exec_tokens.c --->
int								create_heredoc(char *eof,
									t_minishell *minishell);

// exec_tokens_utils.c --->
t_cmds							*create_cmds(char **val);
void							add_cmds_back(t_cmds **list_cmds, t_cmds *new);
int								get_cmds_size(t_token *tokens);

// redirection.c --->
int								redir_in(t_minishell *minishell,
									t_token *current);
int								redir_out(t_minishell *minishell,
									t_token *current);

#endif
