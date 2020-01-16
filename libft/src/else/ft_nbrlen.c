/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:09:49 by apouchet          #+#    #+#             */
/*   Updated: 2019/02/14 17:57:37 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "else.h"

size_t	ft_nbrlen(long nb)
{
	size_t	len;

	len = 0;
	if (nb < 0 && nb <= -10)
	{
		nb = (nb / 10) * -1;
		len = 2;
	}
	else if (nb < 0)
	{
		nb = -nb;
		len = 1;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len + 1);
}
