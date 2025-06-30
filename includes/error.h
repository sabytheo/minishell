/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:33:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/06/30 20:14:06 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define E_MARGS "Error :\nYou have too much arguments.!!!!WRITE USAGE!!!!\n"
# define E_OPENFILE "Error :\nSomething went wrong with SCRIPT FILE\n"
# define E_MALLOC "Error :\nSomething went wrong with your malloc\n"
# define E_PARS_PIPE "minishell: syntax error near unexpected token '|'\n"
# define E_PARS_OPE_D "minishell: syntax error near unexpected token '%s'\n"
# define E_PARS_OPE_E "minishell: syntax error near unexpected token '\\n'\n"
# define E_PARS_CMD_NF "minishell: %s: command not found\n"
# define E_EXPORT_ARG "minishell: export '%s': not a valid identifier\n"
# define E_IS_DIR "minishell: '%s': Is a directory\n"
# define E_NO_PERM "minishell: '%s': Permission denied\n"
# define E_NSFOD "minishell: '%s': No such file or directory\n"
# define E_UNCLOSE_SQUOTE "minishell : syntax error : unclosed single quote\n"
# define E_UNCLOSE_DQUOTE "minishell : syntax error : unclosed double quote\n"
# define E_AFAILED "Error : alloc failed\n"
# define E_NOPWD "%s: error retrieving current directory\n"
# define E_CHDIR "chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"
#endif
