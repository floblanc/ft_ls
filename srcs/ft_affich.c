/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affich.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:28:17 by apouchet          #+#    #+#             */
/*   Updated: 2020/02/04 17:34:46 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		ft_free_ls(t_ls *ls)
{
	size_t i;

	i = 0;
	while (i < ls->nb_elem)
	{
		ft_strdel(&ls->file[i]->name);
		ft_strdel(&ls->file[i]->pathname);
		ft_strdel(&ls->file[i]->user);
		ft_strdel(&ls->file[i]->date);
		ft_strdel(&ls->file[i]->grp);
		ft_strdel(&ls->file[i]->size);
		free(ls->file[i]);
		ls->file[i] = NULL;
		i++;
	}
	free(ls->file);
	ls->file = NULL;
	ft_bzero(&ls->nb_elem, sizeof(size_t) * 10);
}

void		ft_select_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2, size_t *f))
{
	size_t	i;
	size_t	best;
	size_t	pos;
	t_lf	*tmp;

	pos = 0;
	if (!(ls->nb_elem) || ls->flag & FMIN)
		return ;
	while (pos < ls->nb_elem - 1)
	{
		best = pos;
		i = pos + 1;
		while (i < ls->nb_elem)
		{
			if ((!(ls->flag & RMIN)) == !(cmp(ls->file[best]
				, ls->file[i], &(ls->flag))))
				best = i;
			i++;
		}
		tmp = ls->file[best];
		ls->file[best] = ls->file[pos];
		ls->file[pos] = tmp;
		pos++;
	}
}

static void	ft_flag_p_f(mode_t mode, size_t flag, char type[2])
{
	type[0] = '\0';
	if ((flag & PMIN || flag & FMAJ) && (mode & S_IFMT) == S_IFDIR)
		type[0] = '/';
	else if (flag & FMAJ)
	{
		if ((mode & S_IFMT) == S_IFSOCK)
			type[0] = '=';
		else if ((mode & S_IFMT) == S_IFLNK)
			type[0] = '@';
		else if ((mode & S_IFMT) == S_IFWHT)
			type[0] = '%';
		else if ((mode & S_IFMT) == 0150000)
			type[0] = '>';
		else if ((mode & S_IFMT) == S_IFIFO)
			type[0] = '|';
		else if (mode & S_IXUSR)
			type[0] = '*';
	}
	type[1] = '\0';
}

static void	ft_print_data(t_ls *ls, t_lf *file, size_t f, int next)
{
	char	mode[12];
	char	type[2];
	char	link[256];
	ssize_t	len;
	int		go;

	len = 0;
	go = ((f & GMIN) == 0) + ((f & OMIN) == 0) * 2;
	if ((f & LMIN) && file->user != NULL)
	{
		ft_str_mode(mode, file->st.st_mode, file->pathname, file);
		ft_printf("%s %*d %*.*s%*.*s%*s %s ", mode, ls->size_link
			, file->st.st_nlink, (-ls->size_user - 2) * ((f & GMIN) == 0)
			, ls->size_user * ((f & GMIN) == 0), file->user, (-ls->size_grp - 2)
			* ((f & OMIN) == 0), ls->size_grp * ((f & OMIN) == 0), file->grp
			, ls->size_size + (go == 0) * 2 + (f & HMIN) / HMIN, file->size, file->date);
		if (f & LMIN && (file->st.st_mode & S_IFMT) == S_IFLNK)
			if ((len = readlink(file->pathname, link, 256)) < 0)
				ft_exit(3, 0);
	}
	ft_flag_p_f(file->st.st_mode, f, type);
	link[len] = '\0';
	if (((f & LMIN) && file->user) || !(f & LMIN))
		ft_printf("%s%.*s%.*s%.*s%s", file->name, type[0] != 0, type, 4
			* (len > 0), " -> ", len, link, ((f & MMIN) && next ? ", " : "\n"));
}

void		ft_affich(t_ls *ls, int mode)
{
	size_t	i;

	i = 0;
	if (mode != 2 && ls->nb_elem && (ls->flag & SMIN || ls->flag & LMIN))
		ft_printf("total %zu\n", ls->total_block);
	while (i < ls->nb_elem)
	{
		if (ls->file[i]->user != NULL)
		{
			if (ls->flag & IMIN)
				ft_printf("%*zu ", ls->size_ino, ls->file[i]->st.st_ino);
			if (ls->flag & SMIN)
				ft_printf("%*zu ", ls->size_block, ls->file[i]->st.st_blocks);
		}
		ft_print_data(ls, ls->file[i], ls->flag, (ls->file[i + 1] != NULL));
		i++;
	}
	if (!(ls->flag & DMIN) && ls->flag & RMAJ)
		ft_recursif(ls);
	ft_free_ls(ls);
}
