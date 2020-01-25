/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affich.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:28:17 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/25 13:39:55 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

// char	*ft_get_size(size_t size, int h_min)
// {
// 	int		i;
// 	char	letters[] = "BKMGTPEZY";
// 	double	tmp;
// 	char	*ret;
	
// 	if (h_min)
// 	{
// 		i = 0;
// 		tmp = (double)size;
// 		while(tmp / 1024 >= 1)
// 		{
// 			tmp /= 1024;
// 			i++;
// 		}
// 		size = (unsigned int)tmp;
// 		if (tmp >= 10)
// 		{
// 			if (!(ret = itoa((int)size)))
// 				ft_exit(2, 0);
// 			ret[ft_strlen(ret) - 2] = letters[i];
// 		}
// 		else
// 		{
// 			if (!(ret = (char*)ft_memalloc(5)))
// 				ft_exit(2, 0);
// 			ret[0] = (size / 10) + '0';
// 			ret[1] = '.';
// 			ret[2] = (size % 10) + '0';
// 			ret[3] = letters[i];
// 		}
// 		return (ret);
// 	}
// 	if (!(ret = ulltoa(size)))
// 		ft_exit(2, 0);
// 	return (ret);
// }

void	ft_free_ls(t_ls *ls)
{
	size_t i;

	i = 0;
	while (i < ls->size)
	{
		// printf("\ni = %zu\n", i);
		// printf("1 -- %s\n", ls->file[i]->name);
		ft_strdel(&ls->file[i]->name);
		// printf("2 -- %s\n", ls->file[i]->pathname);
		ft_strdel(&ls->file[i]->pathname);
		// printf("3\n");
		// ft_bzero(ls->file[i], sizeof(t_lf));
		free(ls->file[i]);
		ls->file[i] = NULL;
		// printf("4\n");
		i++;
	}
	free(ls->file);
	ls->file = NULL;
	ls->size = 0;
	// printf("end free\n");
}

void	ft_select_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2))
{
	size_t	i;
	size_t	best;
	size_t	pos;
	t_lf			*tmp;

	pos = 0;
	if (!ls->size)
		return ;
	while (pos < ls->size - 1)
	{
		best = pos;
		i = pos + 1;
		// printf("pos = %zu, ls->size %zu\n", pos, ls->size);
		while (i < ls->size)
		{
			// printf("i = %zu\n", i);
			if ((!(ls->flag & RMIN)) == !(cmp(ls->file[best], ls->file[i])))
				best = i;
			i++;
		}
		tmp = ls->file[best];
		ls->file[best] = ls->file[pos];
		ls->file[pos] = tmp;
		pos++;
	}
}

void	ft_bubble_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2))
{
	unsigned int	i;
	t_lf			*tmp;

	i = 1;
	while (i < ls->size)
	{
		// printf("%d == %d\n", (!(ls->flag & RMIN)), (cmp(ls->file[i - 1], ls->file[i])));
		if ((!(ls->flag & RMIN)) == !(cmp(ls->file[i - 1], ls->file[i])))
		{
			tmp = ls->file[i - 1];
			ls->file[i - 1] = ls->file[i];
			ls->file[i] = tmp;
			i = 0;
		}
		i++;
	}
}

void	ft_affich(t_ls *ls)
{
	int i;

	i = 0;
	if (ls->flag & SMAJ)
		ft_select_sort(ls, &ft_less_s_maj_cmp);
	else if (ls->flag & TMIN)
		ft_select_sort(ls, &ft_less_t_cmp);
	else
		ft_select_sort(ls, &ft_ascii_cmp);
	while (i < ls->size)
	{
		ft_printf("%s\n", ls->file[i++]->name);
	}
	if (ls->flag & RMAJ)
		ft_recursif(ls);
	ft_free_ls(ls);

}
