/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:34:58 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/29 16:58:30 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdbool.h>

typedef struct s_expand
{
	char *expanded;
	bool in_squote;
	bool in_dquote;

}			t_expand;

#endif
