/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:41:04 by makurek           #+#    #+#             */
/*   Updated: 2025/02/26 15:39:19 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;

	first = NULL;
	while (lst)
	{	
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
