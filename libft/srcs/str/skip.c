/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:54:00 by makurek           #+#    #+#             */
/*   Updated: 2024/12/23 15:50:27 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *skip(const char *str, int is_something(const char))
{
    while (is_something(*str))
        str++;
    return ((char *)str);
}
