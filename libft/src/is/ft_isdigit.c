/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:09:03 by apouchet          #+#    #+#             */
/*   Updated: 2018/11/27 17:09:04 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is.h"

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
