/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:40:21 by makurek           #+#    #+#             */
/*   Updated: 2024/12/23 15:44:18 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(const int c)
{
	return (c >= 'A' && c <= 'Z');
}

static int	ft_islower(const int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isalpha(const int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
