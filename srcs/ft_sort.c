/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:27:27 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/29 13:19:40 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		ft_ascii_cmp(t_lf *f1, t_lf *f2, size_t *flag)
{
	(void)flag;
	return ((ft_strcmp(f1->name, f2->name)) <= 0);
}

int		ft_less_s_maj_cmp(t_lf *f1, t_lf *f2, size_t *flag)
{
	(void)flag;
	if (f1->st.st_size == f2->st.st_size)
		return (ft_ascii_cmp(f1, f2, flag));
	return (f1->st.st_size > f2->st.st_size);
}

int		ft_less_t_cmp(t_lf *f1, t_lf *f2, size_t *flag)
{
	double	diff;

	if (*flag & CMIN)
		diff = difftime(f1->st.st_mtime, f2->st.st_mtime);
	else if (*flag & UMIN)
		diff = difftime(f1->st.st_atime, f2->st.st_atime);
	else if (*flag & UMAJ)
		diff = difftime(f1->st.st_birthtime, f2->st.st_birthtime);
	if ((ssize_t)diff == 0)
		return (ft_ascii_cmp(f1, f2, flag));
	return (diff > 0);
}
