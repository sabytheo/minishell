/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:41:16 by tsaby             #+#    #+#             */
/*   Updated: 2024/11/14 15:50:20 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*newlstptr;
	void	*result;

	newlstptr = NULL;
	while (lst != NULL)
	{
		result = f(lst->content);
		tmp = ft_lstnew(result);
		if (!tmp)
		{
			del(result);
			ft_lstclear(&newlstptr, del);
			return (NULL);
		}
		ft_lstadd_back(&newlstptr, tmp);
		lst = lst->next;
	}
	return (newlstptr);
}
