/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:03:40 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/19 16:31:21 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include "token.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
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

typedef struct s_minishell
{
	int		launch_mode;
	int		input_fd;
	char	**envp_copy;
	bool	is_running;

}			t_minishell;

enum		e_launch_modes
{
	TTY_MODES,
	SCRIPT_MODES,
	HERE_DOC_MODES
};

// Clean.c --->
void		free_minishell(t_minishell *minishell);

// main.c --->
void		clean_error(char *error_message, t_minishell *minishell);
void		check_args_count(int argc, char **argv, t_minishell *minishell);
char		*get_entry(t_minishell *minishell);

// init.c --->
void			init_minishell(t_minishell *minishell, char **envp);
void		copy_envp(char **envp, t_minishell *minishell);

// token.c --->
t_token	*define_token(char *line);

#endif
