/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:40:59 by makurek           #+#    #+#             */
/*   Updated: 2024/12/11 14:45:52 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void ft_dlstiter(t_dnode *lst, void (*f)(void*))
{
    if (!f)
        return;
    while (lst)
    {
        f(lst->data);
        lst = lst->next;
    }
}

