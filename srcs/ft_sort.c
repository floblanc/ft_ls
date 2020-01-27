/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:27:27 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 23:51:13 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		ft_ascii_cmp(t_lf *f1, t_lf *f2)
{
	return ((ft_strcmp(f1->name, f2->name)) <= 0);
}

int		ft_less_s_maj_cmp(t_lf *f1, t_lf *f2)
{
	if (f1->st.st_size == f2->st.st_size)
		return (ft_ascii_cmp(f1, f2));
	return (f1->st.st_size > f2->st.st_size);
}

int		ft_less_t_cmp(t_lf *f1, t_lf *f2)
{
	double	diff;

	diff = difftime(f1->st.st_mtime, f2->st.st_mtime);
	if ((ssize_t)diff == 0)
		return (ft_ascii_cmp(f1, f2));
	return (diff > 0);
}


// -c      Use time when file status was last changed for sorting (-t)
//              or long printing (-l).

// -f      Output is not sorted.  This option turns on the -a option.

// -u      Use time of last access, instead of last modification of
//              the file for sorting (-t) or long printing (-l).

// -U      Use time of file creation, instead of last modification for
//      sorting (-t) or long output (-l).
