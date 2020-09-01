/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:04:01 by apouchet          #+#    #+#             */
/*   Updated: 2020/09/01 12:28:00 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void		ft_sort_to_read(t_ls *ls, int try)
{
	size_t i;

	i = 0;
	if (try == 0)
		(ls->flag & DMIN) == 0 ? (ls->dir_read[ls->nb_dir++] = ft_strdup("."))
		: (ls->file_read[ls->nb_file++] = ft_strdup("."));
	if (ls->nb_dir)
	{
		if (!(ls->current_path = ft_strdup("."))
			|| !(ls->file = (t_lf**)ft_memalloc(8 * (size_t)(ls->nb_dir + 1))))
			ft_exit(2, 0);
		while (ls->dir_read[i])
		{
			ft_new_file(ls, ls->dir_read[i]);
			ft_strdel(&ls->dir_read[i++]);
		}
		ft_long_format(ls, 0);
		i = 0;
		while (i < ls->nb_dir)
		{
			ls->dir_read[i] = ft_strdup(ls->file[i]->name);
			i++;
		}
		ft_free_ls(ls);
	}
}

static void		ft_get_to_read(t_ls *ls, int size, int argc, char **argv)
{
	int			i;
	struct stat st;

	i = 0;
	if (!(ls->dir_read = (char**)ft_memalloc(8 * (size_t)(size + 1)))
		|| !(ls->file_read = (char**)ft_memalloc(8 * (size_t)(size + 1))))
		ft_exit(2, 0);
	while (++i < argc)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && !argv[i][1]) || ls->try)
		{
			(ls->try)++;
			if (lstat(argv[i], &st) == -1)
				ft_printf("ft_ls: %s: %s\n", argv[i], strerror(errno));
			else if ((st.st_mode & S_IFMT) == S_IFDIR && !(ls->flag & DMIN))
				ls->dir_read[ls->nb_dir++] = ft_strdup(argv[i]);
			else
				ls->file_read[ls->nb_file++] = ft_strdup(argv[i]);
		}
	}
	ft_sort_to_read(ls, ls->try);
	ft_strdel(&ls->current_path);
}

static void		ft_chose_flag(char letter, size_t *flag)
{
	if (letter == 'p')
		*flag &= (0xFFFFFFFF - FMAJ);
	else if (letter == 'F')
		*flag &= (0xFFFFFFFF - PMIN);
	else if (letter == 'l' || letter == 'o' || letter == 'n' || letter == 'g')
		*flag &= (0xFFFFFFFF - MMIN);
	else if (letter == 'm')
		*flag &= (0xFFFFFFFF - LMIN);
	else if (letter == 'U')
		*flag &= (0xFFFFFFFF - (UMIN + CMIN));
	else if (letter == 'u')
		*flag &= (0xFFFFFFFF - (UMAJ + CMIN));
	else if (letter == 'c')
		*flag &= (0xFFFFFFFF - (UMIN + UMAJ));
}

static int		flag_stocker(char letter, size_t *flag)
{
	int	i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == letter)
		{
			*flag |= (size_t)ft_pow(2, i);
			ft_chose_flag(letter, flag);
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

	i = 0;
	size = 0;
	ft_bzero(ls, sizeof(t_ls));
	ls->flag |= CMIN;
	while (++i < argc)
	{
		if (!(size) && argv[i][0] == '-' && argv[i][1])
		{
			j = 0;
			while (argv[i][++j])
				if (size || !(flag_stocker(argv[i][j], &(ls->flag))))
					ft_exit(1, argv[i][j]);
		}
		else
			size++;
	}
	if (ls->flag & OMIN || ls->flag & NMIN || ls->flag & GMIN)
		ls->flag |= ((ls->flag & MMIN) == 0 ? LMIN : 0);
	if (ls->flag & FMIN)
		ls->flag |= AMIN;
	ft_get_to_read(ls, (size == 0 ? 1 : size), argc, argv);
}
