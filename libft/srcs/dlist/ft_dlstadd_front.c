/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:40:46 by makurek           #+#    #+#             */
/*   Updated: 2024/12/06 22:41:48 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void ft_dlstadd_front(t_dnode **dlst, t_dnode *new)
{
    if (dlst && *dlst)
    {
        new->next = *dlst;
        (*dlst)->prev = new;
        *dlst = new;
    }
    else if (dlst)
        *dlst = new;
}
