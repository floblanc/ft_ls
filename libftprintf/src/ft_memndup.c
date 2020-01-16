/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:17:01 by floblanc          #+#    #+#             */
/*   Updated: 2019/06/26 15:40:51 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

void	*ft_memndup(unsigned char *s, size_t n)
{
	size_t			i;
	unsigned char	*dst;

	i = 0;
	if (!(dst = (unsigned char*)malloc(sizeof(unsigned char) * (n))))
		return (0);
	while (s[i] && i < n)
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}
