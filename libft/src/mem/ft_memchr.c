/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:12:05 by apouchet          #+#    #+#             */
/*   Updated: 2019/02/14 18:09:14 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *a;

	a = (const unsigned char*)s;
	while (n--)
	{
		if (*a == (const unsigned char)c)
			return ((void*)((size_t)a));
		a++;
	}
	return (NULL);
}
