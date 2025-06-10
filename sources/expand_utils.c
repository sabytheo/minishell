/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/27 14:47:33 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c, int len) {
  if (len == 0)
    return (ft_isalpha(c) || c == '_' || c == '?');
  return (ft_isalnum(c) || c == '_');
}

int	envp_size(t_denvp *envp) {
  t_denvp *current;
  int len;

  len = 0;
  current = envp;
  while (current != NULL) {
    current = current->next;
    len++;
  }
  free(current);
  return (len);
}

void	chainedlst_to_tab(t_minishell *minishell) {
  t_denvp *current;
  int i;

  if (minishell->envp_tab)
    free_tab(minishell->envp_tab);
  minishell->envp_countline = envp_size(minishell->envp);
  current = minishell->envp;
  i = 0;
  minishell->envp_tab =
      malloc(sizeof(char *) * (minishell->envp_countline + 1));
  if (minishell->envp_tab == NULL)
    return ;
  while (current) {
    minishell->envp_tab[i] = ft_strjoin(current->var[0], current->var[1]);
    i++;
    current = current->next;
  }
  minishell->envp_tab[i] = NULL;
}
