/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:20:09 by maginist          #+#    #+#             */
/*   Updated: 2019/06/18 14:53:28 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

int	ft_charstr2(char *s1, char *s2, int i, int j)
{
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] != s2[j])
		{
			if (s2[j + 1] == '\0' && s1[i] != s2[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_charstr(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	if (!((s1) || (s2)))
		return (0);
	while (s2[i])
	{
		j = i + 1;
		while (s2[j])
		{
			if (s2[i] == s2[j])
				return (0);
			j++;
		}
		i++;
	}
	if (ft_charstr2(s1, s2, i, j) == 1)
		return (1);
	else
		return (0);
}
