/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 23:33:03 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 15:46:35 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_nb(ssize_t nb, size_t base)
{
	size_t	len;
	size_t	a;

	len = 1;
	a = (size_t)nb;
	if (nb < 0)
		a = (size_t)-nb;
	while (a >= (unsigned)base)
	{
		a = a / base;
		len++;
	}
	return (len);
}

static size_t	ft_nb_unsigned(size_t nb, size_t base)
{
	size_t	len;
	size_t	a;

	len = 1;
	a = nb;
	while (a >= base)
	{
		a = a / base;
		len++;
	}
	return (len);
}

char			*ft_itoa_base(ssize_t nb, size_t base, int maj)
{
	size_t	i;
	size_t	n;
	char	*tab;

	i = ft_nb(nb, base);
	if (base < 2 || base > 36 || !(tab = (char*)malloc(i + 1)))
		return (NULL);
	tab[i--] = '\0';
	n = (size_t)nb;
	if (nb < 0)
		n = (size_t)-nb;
	while (n >= (unsigned)base)
	{
		if (n % base < 10)
			tab[i--] = '0' + (char)(n % base);
		else
			tab[i--] = (char)('a' - 10 - (32 * maj)) + (char)(n % base);
		n = n / base;
	}
	if (n % base < 10)
		tab[i] = '0' + (char)n;
	else
		tab[i] = (char)('a' - 10 - (32 * maj)) + (char)n;
	return (tab);
}

char			*ft_itoa_unsigned_base(size_t nb, size_t base, int maj)
{
	size_t	i;
	size_t	n;
	char	*tab;

	i = ft_nb_unsigned(nb, base);
	if (base < 2 || base > 36 || !(tab = (char*)malloc(i + 1)))
		return (NULL);
	tab[i--] = '\0';
	n = nb;
	while (n >= (unsigned)base)
	{
		if (n % base < 10)
			tab[i--] = '0' + (char)(n % base);
		else
			tab[i--] = (char)('a' - 10 - (32 * maj)) + (char)(n % base);
		n = n / base;
	}
	if (n % base < 10)
		tab[i] = '0' + (char)n;
	else
		tab[i] = (char)('a' - 10 - (32 * maj)) + (char)n;
	return (tab);
}
