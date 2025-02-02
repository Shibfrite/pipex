/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:41:07 by makurek           #+#    #+#             */
/*   Updated: 2024/12/11 12:55:29 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*chain;

	chain = malloc(sizeof(*chain));
	if (!chain)
		return (NULL);
	chain->content = content;
	chain->next = NULL;
	return (chain);
}
