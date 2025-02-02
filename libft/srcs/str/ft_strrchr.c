/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:42:14 by makurek           #+#    #+#             */
/*   Updated: 2024/10/07 18:24:17 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last;

	last = NULL;
	while (*str)
		if (*str++ == (unsigned char)c)
			last = str - 1;
	if (*str == (unsigned char)c)
		return ((char *)str);
	else
		return ((char *)last);
}
