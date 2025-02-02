/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:41:07 by makurek           #+#    #+#             */
/*   Updated: 2024/12/11 14:54:27 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

t_dnode *ft_dlstnew(void *data)
{
    t_dnode *chain;

    chain = malloc(sizeof(*chain));
    if (!chain)
        return (NULL);
    chain->data = data;
    chain->prev = NULL;
    chain->next = NULL;
    return (chain);
}
