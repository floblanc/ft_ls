/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:24 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/17 12:24:52 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

unsigned int	ft_abs(int nb)
{
	if (nb < 0)
		return ((unsigned int)(-nb));
	return ((unsigned int)nb);
}
