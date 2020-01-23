/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:27:27 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/23 18:14:17 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		ft_ascii_cmp(t_lf *f1, t_lf *f2)
{
	return ((ft_strcmp(f1->name, f2->name)) <= 0);
}

int		ft_less_s_maj_cmp(t_lf *f1, t_lf *f2)
{
	if (f1->file_size == f2->file_size)
		return (ft_ascii_cmp(f1, f2));
	return (f1->file_size > f2->file_size);
}

int		ft_less_t_cmp(t_lf *f1, t_lf *f2)
{
	double	diff;

	diff = difftime(f1->mtime, f2->mtime);
	if ((ssize_t)diff == 0)
		return (ft_ascii_cmp(f1, f2));
	return (diff > 0);
}