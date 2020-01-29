/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:04:01 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/28 22:59:59 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void		ft_get_to_read(t_ls *ls, int size, int argc, char **argv)
{
	int			i;
	int			file;
	int			dir;
	struct stat st;

	i = 1;
	dir = 0;
	file = 0;
	if (size == 0)
		size = 1;
	if (!(ls->dir_read = (char**)ft_memalloc(8 * (size_t)(size + 1)))
		|| !(ls->file_read = (char**)ft_memalloc(8 * (size_t)(size + 1))))
		ft_exit(2, 0);
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			if (lstat(argv[i], &st) == -1)
				ft_printf("lstat : parsing ft_ls: %s: %s\n", argv[i], strerror(errno));
			else
			{
				if ((st.st_mode & S_IFMT) == S_IFDIR)
					ls->dir_read[dir++] = ft_strdup(argv[i]);
				else
					ls->file_read[file++] = ft_strdup(argv[i]);
			}
		}
		i++;
	}
	if (dir < 0)
		ls->dir_read[dir] = ft_strdup(".");
	// if (size > 1 && dir > 0)
		// ft_printf("%s:\n", ls->dir_read[0]);
}

static void		ft_chose_flag(char letter, size_t *flag)
{
	if (letter == 'p')
		*flag &= (0xFFFFFFFF - FMAJ);
	else if (letter == 'F')
		*flag &= (0xFFFFFFFF - PMIN);
	else if (letter == 'l')
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
	*flag |= CMIN;
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

	i = 1;
	size = 0;
	ft_bzero(ls, sizeof(t_ls));
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			while (argv[i][++j])
				if (!(flag_stocker(argv[i][j], &(ls->flag))))
					ft_exit(1, argv[i][j]);
		}
		else
			size++;
		i++;
	}
	if (ls->flag & OMIN || ls->flag & NMIN || ls->flag & GMIN)
		ls->flag |= LMIN;
	if (ls->flag & FMIN)
		ls->flag |= AMIN;
	ft_get_to_read(ls, size, argc, argv);
}
