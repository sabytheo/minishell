/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:47:35 by egache            #+#    #+#             */
/*   Updated: 2025/05/27 11:43:08 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strldup(char *src, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (!src)
	{
		dest[i] = '\0';
		return (dest);
	}
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}



static char	**fill_variables(char *value)
{
	char	**var;
	int		size1;
	int		size2;

	size1 = ft_strlen_equal(value);
	size2 = ft_strlen(value) - size1;
	var = malloc(sizeof(char *) * 3);
	if (var == NULL)
		return (NULL); // need free
	var[2] = NULL;
	var[0] = ft_strldup(value, size1);
	if (value[size1] != '\0')
		var[1] = ft_strldup(&value[size1], size2);
	else
		var[1] = NULL;
	return (var);
}

t_denvp	*create_denvp(char **var)
{
	t_denvp	*new;

	new = malloc(sizeof(t_denvp));
	if (!new)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}

void	add_denvp_back(t_denvp **list_denvp, t_denvp *new)
{
	t_denvp	*tmp;

	if (!*list_denvp)
	{
		*list_denvp = new;
		return ;
	}
	tmp = *list_denvp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

bool	display_export(t_minishell *minishell)
{
	t_denvp	*current;

	if (minishell->cmds->args[1] == NULL)
	{
		current = minishell->export;
		while (current != NULL)
		{
			printf("export %s", current->var[0]);
			if (current->var[1] != NULL)
				printf("%s", current->var[1]);
			printf("\n");
			current = current->next;
		}
		return (true);
	}
	return (false);
}

bool	already_exist(t_minishell *minishell, t_denvp *list)
{
	t_denvp	*current;
	char	**args;

	args = fill_variables(minishell->cmds->args[1]);
	current = list;
	while (current != NULL)
	{
		if (ft_strcmp(args[0], list->var[0]) == 0)
		{
			if (ft_strcmp(args[1], list->var[1]) == 0)
			{
				free_tab(args);
				return (true);
			}
		}
		current = current->next;
	}
	free_tab(args);
	return (false);
}

static bool	valid_id(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (true);
	else
		return (false);
}

static int	export_parsing(char *str)
{
	int	i;

	if (str[0] != '_' && ft_isalpha(str[0]) == 0)
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i = 1;
			while (str[i] != '=')
			{
				if (valid_id(str[i]) == false || ft_isalpha(str[0] == 0))
					return (1);
				i++;
			}
			return (0);
		}
		else
		{
			if (valid_id(str[i]) == false || ft_isalpha(str[0]) == 0)
				return (1);
			i++;
		}
	}
	return (2);
}
bool	replace_node(t_denvp *current, char *arg)
{
	int	size1;
	int	size2;

	size1 = ft_strlen_equal(arg);
	size2 = ft_strlen(arg) - size1;
	while (current)
	{
		if (ft_strncmp(arg, current->var[0], ft_strlen(current->var[0])) == 0)
		{
			if (arg[size1] != '\0')
			{
				free(current->var[1]);
				current->var[1] = ft_strldup(&arg[size1], size2);
			}
			return (true);
		}
		current = current->next;
	}
	return (false);
}

void	add_to_list(t_minishell *minishell, t_denvp *list)
{
	t_denvp	*current;
	t_denvp	*new;
	char	**var;

	current = list;
	while (current != NULL && current->next != NULL)
		current = current->next;
	var = fill_variables(minishell->cmds->args[1]);
	new = create_denvp(var);
	current = list;
	add_denvp_back(&current, new);
}

void	split_envp(t_minishell *minishell, char **envp)
{
	t_denvp	*new_denvp;
	t_denvp	*new_export;
	int		i;
	char	**var1;
	char	**var2;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		var1 = fill_variables(envp[i]);
		var2 = fill_variables(envp[i]);
		new_export = create_denvp(var1);
		new_denvp = create_denvp(var2);
		add_denvp_back(&minishell->export, new_export);
		add_denvp_back(&minishell->denvp, new_denvp);
		i++;
	}
	return ;
}

void	ft_export(t_minishell *minishell)
{
	if (display_export(minishell) == true)
		return ;
	if (already_exist(minishell, minishell->export) == true)
		return ;
	if (export_parsing(minishell->cmds->args[1]) == 0)
	{
		if (replace_node(minishell->export, minishell->cmds->args[1]) == false)
			add_to_list(minishell, minishell->export);
		if (replace_node(minishell->denvp, minishell->cmds->args[1]) == false)
			add_to_list(minishell, minishell->denvp);
	}
	else if (export_parsing(minishell->cmds->args[1]) == 2)
	{
		if (replace_node(minishell->export, minishell->cmds->args[1]) == false)
			add_to_list(minishell, minishell->export);
	}
	else
	{
		minishell->error_code = 1;
		ft_printf_fd(2, E_EXPORT_ARG, minishell->cmds->args[1]);
	}
	return ;
}
