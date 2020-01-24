/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affich.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:28:17 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/24 14:47:09 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

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
		ft_bubble_sort(ls, &ft_less_s_maj_cmp);
	else if (ls->flag & TMIN)
		ft_bubble_sort(ls, &ft_less_t_cmp);
	else
		ft_bubble_sort(ls, &ft_ascii_cmp);
	while (i < ls->size)
	{
		ft_printf("%s\n", ls->file[i++]->name);
	}
	if (ls->flag & RMAJ)
		ft_recursif(ls);
}
