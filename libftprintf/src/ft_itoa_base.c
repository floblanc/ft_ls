/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:35:03 by maginist          #+#    #+#             */
/*   Updated: 2019/07/23 18:06:08 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

int		find_size(int value, char *base)
{
	int	size;
	int	size_base;

	size_base = ft_strlen(base);
	size = 0;
	if (value <= 0)
		size++;
	while (value != 0)
	{
		value /= size_base;
		size++;
	}
	return (size);
}

char	*ft_itoa_base(int value, char *base)
{
	int		neg;
	char	*str;
	int		size;
	int		base_len;

	neg = 1;
	base_len = ft_strlen(base);
	size = find_size(value, base);
	if (value < 0)
		neg = -1;
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (0);
	if (neg == -1)
		str[0] = '-';
	str[size--] = '\0';
	while (size >= 0 && str[size] != '-')
	{
		str[size--] = base[value % base_len];
		value /= base_len;
	}
	return (str);
}
