/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:15:26 by apouchet          #+#    #+#             */
/*   Updated: 2018/11/29 15:15:29 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strdup_free(char **s1)
{
	char *a;

	if (!(a = (char*)ft_memalloc(sizeof(char) * (ft_strlen(*s1) + 1))))
		return (NULL);
	a = ft_strcpy(a, *s1);
	ft_strdel(s1);
	return (a);
}
