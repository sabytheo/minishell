/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:33:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/06 18:44:38 by egache           ###   ########.fr       */
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

#endif
