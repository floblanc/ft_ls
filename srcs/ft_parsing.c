/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:04:01 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 19:18:19 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void		ft_get_to_read(t_ls *ls, int size, int argc, char **argv)
{
	int i;
	int nb;

	i = 1;
	nb = 0;
	if (size == 0)
		size = 1;
	if (!(ls->to_read = (char**)malloc((sizeof(char*) * (size_t)(size + 1)))))
		ft_exit(2, 0);
	ls->to_read[size] = NULL;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			ls->to_read[nb++] = ft_strdup(argv[i]);
		i++;
	}
	if (nb == 0)
		ls->to_read[nb] = ft_strdup(".");
}

static int		flag_stocker(char letter, size_t *flag)
{
	int	i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == letter)
		{
			*flag = *flag | (size_t)ft_pow(2, i);
			if (FLAGS[i] == 'p')
				*flag &= (0xFFFF - FMAJ);
			else if (FLAGS[i] == 'F')
				*flag &= (0xFFFF - PMIN);
			return (1);
		}
		i++;
	}
	return (0);
}

void			ft_get_flag(t_ls *ls, int argc, char **argv)
{
	int i;
	int j;
	int	size;

	i = 1;
	size = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (!(flag_stocker(argv[i][j], &(ls->flag))))
					ft_exit(1, argv[i][j]);
				j++;
			}
		}
		else
			size++;
		i++;
	}
	if (ls->flag & OMIN || ls->flag & NMIN)
		ls->flag |= LMIN;
	ft_get_to_read(ls, size, argc, argv);
}
