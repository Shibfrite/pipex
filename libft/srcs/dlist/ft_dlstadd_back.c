/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:40:42 by makurek           #+#    #+#             */
/*   Updated: 2024/12/06 22:41:06 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void ft_dlstadd_back(t_dnode **dlst, t_dnode *new)
{
    t_dnode *last;

    if (dlst && *dlst)
    {
        last = ft_dlstlast(*dlst);
        last->next = new;
        new->prev = last;
    }
    else if (dlst)
        *dlst = new;
}
