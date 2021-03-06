/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:21:24 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/17 12:23:28 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

double	ft_abs_double(double f)
{
	if (f < 0)
		return (-f);
	return (f);
}
