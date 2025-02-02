/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:40:51 by makurek           #+#    #+#             */
/*   Updated: 2024/12/11 14:45:18 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void ft_dlstdelone(t_dnode *lst, void (*del)(void*))
{
    if (!lst || !del)
        return ;
    del(lst->data);
    free(lst);
}
