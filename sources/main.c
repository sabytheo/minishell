/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:34 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/11 19:21:09 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (void)
{
 	char *entry;

	while (1)
	{
		entry = readline("Minishell>");
		add_history(entry);
		free(entry);
	}
	return (0);
}
