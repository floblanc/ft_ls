/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:09:33 by apouchet          #+#    #+#             */
/*   Updated: 2020/02/03 17:18:57 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

double		ft_pow_double(double x, double y)
{
	double a;

	a = x;
	if ((int)y == 0)
		return (1);
	if ((int)x == 1 || (int)x == 0 || (int)y == 1)
		return (x);
	while (y > 1)
	{
		x = x * a;
		y--;
	}
	return (x);
}

ssize_t		ft_pow(ssize_t x, ssize_t y)
{
	ssize_t a;

	a = x;
	if ((int)y == 0)
		return (1);
	if ((int)x == 1 || (int)x == 0 || (int)y == 1)
		return (x);
	while (y > 1)
	{
		x = x * a;
		y--;
	}
	return (x);
}
