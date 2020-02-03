/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:09:49 by apouchet          #+#    #+#             */
/*   Updated: 2020/02/03 17:18:50 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

size_t	ft_nbrlen_unsigned(size_t nb)
{
	size_t	len;

	len = 0;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len + 1);
}
