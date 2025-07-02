/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:45:12 by egache            #+#    #+#             */
/*   Updated: 2025/07/02 16:05:00 by egache           ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
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

typedef struct s_denvp
{
	char						**var;
	struct s_denvp				*next;
}								t_denvp;

typedef struct s_heredoc
{
	char						*filename;
	struct s_heredoc			*next;
}								t_heredoc;

typedef struct s_minishell
{
	int							launch_mode;
	int							input_fd;
	int							output_fd;
	int							saved_inputfd;
	int							saved_outputfd;
	int							h_fd;
	int							error_code;
	char						*error_item;
	char						**envp_tab;
	int							envp_countline;
	int							fd;
	int							cmds_count;
	int							**pipes;
	pid_t						*pids;
	bool						is_running;
	bool						errfound;
	bool						cmdfound;
	int							shlvl;
	char						*entry;
	char						*path;
	t_heredoc					*heredoc;
	t_token						*tokens;
	t_expand					*expand;
	t_denvp						*envp;
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
void							free_minishell(t_minishell *minishell,
									char *error_message, bool exit_needed);
void							free_running_minishell(t_minishell *minishell);
void							free_exit_pipes(t_minishell *minishell);

void							free_heredoc(t_heredoc **heredoc);
;
// clean_child.c --->

int								exit_and_clear_child_pipe(int error_code,
									t_minishell *minishell);
int								exit_and_clear_child(int error_code,
									t_minishell *minishell);

// clean_lst.c --->

void							free_tokens(t_token **tokens);
void							free_tab(char **tab);
void							free_cmds(t_cmds **cmds);
void							free_denvp(t_denvp **envp);

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

// init.c --->
int								fill_envp(t_minishell *minishell, char **envp);
int								fill_envpnull(t_minishell *minishell,
									char *var);
int								define_shlvl(t_denvp **list);

// tokens.c --->
bool							has_closed_quotes(char *str, bool message);
void							define_tokens(char *line,
									t_minishell *minishell);
void							format_tokens(t_token *tokens,
									t_minishell *minishell);
int								tokens(t_minishell *minishell, char *entry);

// format_tokens_utils.c --->
char							*remove_quotes(const char *str);

// check_tokens.c --->
bool							check_tokens(t_minishell *minishell);
char							*check_syntax(t_minishell *minishell);

// check_cmd.c --->
bool							check_cmd(t_minishell *minishell, char *arg);
void							check_ifcmdempty(t_minishell *minishell);
bool							check_filetype(t_minishell *minishell,
									char *arg);
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
char							*append_char(t_expand *expand, char c);
bool							should_expand(char *str, int i);
char							*append_and_free(char *base, char *addition);

// chainedlst_totab.c --->
void							chainedlst_to_tab(t_minishell *minishell);
int								envp_size(t_denvp *envp);

// debug.c --->
void							print_tokens(t_token *tokens);
void							print_cmds(t_cmds *cmds);

// signals.c --->
void							signal_initialisation(void);
void							signal_ignore(void);
void							disable_control_echo(void);

// signals_handler.c
void							signal_handler(int signum);
void							heredoc_signal_handler(int signum);
int								stop_readline(void);

// builtins.c --->
int								ft_echo(t_cmds **cmds);
int								ft_cd(t_minishell *minishell, t_cmds **cmds);
int								ft_pwd(void);
int								update_pwd(t_minishell *minishell);
int								ft_env(t_minishell *minishell);
int								ft_unset(t_minishell *minishell);
void							ft_exit(t_minishell *minishell, int state);

// export.c --->
int								ft_export(t_minishell *minishell, t_cmds *cmds);
char							**fill_variables_envp(char *value);
void							*free_variables_tab_null(char **var);

// export_list_export.c --->
char							**join_and_dup_export(char **var, char *value,
									int size1, int size2);
void							export_add_export(t_minishell *minishell,
									t_denvp **export, char *arg);
char							*replace_variable_export(char *var, char *arg,
									int size1, int size2);
bool							replace_node_export(t_minishell *minishell,
									t_denvp *current, char *arg);
char							**fill_variables_export(char *value);

// export_check.c
bool							export_display(t_minishell *minishell);
int								export_parsing(char *str);
bool							already_exist(t_minishell *minishell,
									t_denvp *list, char *arg);

// export_utils.c
int								ft_strlen_equal(char *str);
t_denvp							*create_denvp(char **var);
void							add_denvp_back(t_denvp **list_denvp,
									t_denvp *new);
bool							valid_id(char c);
void							add_to_list_envp(t_minishell *minishell,
									t_denvp **list, char *arg);
void							add_to_list_export(t_minishell *minishell,
									t_denvp **list, char *arg);
// find_path.c --->
char							*find_path(char *arg, char **envp);
int								exec_builtins(t_minishell *minishell,
									t_cmds *cmds);

// exec_tokens.c --->
void							exec_tokens(t_minishell *minishell);
int								create_heredoc(char *limiter,
									t_minishell *minishell, t_token *redir);

// exec_tokens_utils.c --->
t_cmds							*create_cmds(char **val);
void							add_cmds_back(t_cmds **list_cmds, t_cmds *new);
int								get_cmds_size(t_token *tokens);
t_token							*duplicate_token(t_token *token);
void							add_redir_to_list(t_token **redir_head,
									t_token **redir_tail,
									t_token *redir_token_copy,
									t_token *file_token_copy);
void							next_tokens(t_token **current_args,
									t_token **current_redir);
void							add_and_lastcheck(t_minishell *minishell,
									t_cmds *new, char **args);

// setup_redirection.c --->
int								setup_redirections(t_token *current,
									t_minishell *minishell, bool cmdfound);
int								redir_in(t_minishell *minishell,
									t_token *current, bool cmdfound);
int								redir_out(t_minishell *minishell,
									t_token *current, bool cmdfound);
int								redir_append(t_minishell *minishell,
									t_token *current, bool cmdfound);
void							reset_redir(t_minishell *minishell);

// exec_single.c --->
void							execute_single_command(t_minishell *minishell);
void							wait_thechild(pid_t pid,
									t_minishell *minishell);
int								single_builtins(t_cmds *cmds,
									t_minishell *minishell);
// exec_pipes.c --->
void							execute_piped_command(t_minishell *minishell,
									t_cmds *cmds);

// exec_pipes_utils.c --->
void							getcmd_count(t_minishell *minishell);
void							cleanup_pipes(int **pipes, int pipe_count);
void							close_pipes_inchild(t_minishell *minishell);

void							add_heredoc_back(t_heredoc **list_heredoc,
									t_heredoc *new);
t_heredoc						*create_heredoc_node(char *filename);
void							cleanup_heredocs(t_minishell *minishell);
int								prepare_heredocs(t_minishell *minishell,
									t_cmds *cmds);
int								create_list(char *filename,
									t_minishell *minishell);

void							free_cmds_child(t_cmds **cmds);

#endif
