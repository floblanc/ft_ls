/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affich.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:28:17 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 12:50:53 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
#include <sys/acl.h>

void	ft_free_ls(t_ls *ls)
{
	size_t i;

	i = 0;
	while (i < ls->nb_elem)
	{
		ft_strdel(&ls->file[i]->name);
		ft_strdel(&ls->file[i]->pathname);
		ft_strdel(&ls->file[i]->user);
		ft_strdel(&ls->file[i]->grp);
		ft_strdel(&ls->file[i]->size);
		free(ls->file[i]);
		ls->file[i] = NULL;
		i++;
	}
	free(ls->file);
	ls->file = NULL;
	ft_bzero(&ls->nb_elem, sizeof(size_t) * 7);
}

void	ft_select_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2))
{
	size_t	i;
	size_t	best;
	size_t	pos;
	t_lf			*tmp;

	pos = 0;
	if (!ls->nb_elem)
		return ;
	while (pos < ls->nb_elem - 1)
	{
		best = pos;
		i = pos + 1;
		// printf("pos = %zu, ls->nb_elem %zu\n", pos, ls->nb_elem);
		while (i < ls->nb_elem)
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
	while (i < ls->nb_elem)
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

// b     Block special file.
// c     Character special file.
// d     Directory.
// l     Symbolic link.
// s     Socket link.
// p     FIFO.
// -     Regular file.

// S_IFMT	0170000	masque du type de fichier
// S_IFSOCK	0140000	socket
// S_IFLNK	0120000	lien symbolique
// S_IFREG	0100000	fichier ordinaire
// S_IFBLK	0060000	périphérique blocs
// S_IFDIR	0040000	répertoire
// S_IFCHR	0020000	périphérique caractères
// S_IFIFO	0010000	fifo


void	ft_str_mode(char src[12], mode_t mode)
{
	static char	str[] = "rwxrwxrwx";
	int			i;
	acl_t		acl = NULL;

	if ((mode & S_IFMT) == S_IFSOCK)
		src[0] = 's';
	else if ((mode & S_IFMT) == S_IFLNK)
		src[0] = 'l';
	else if ((mode & S_IFMT) == S_IFREG)
		src[0] = '-';
	else if ((mode & S_IFMT) == S_IFBLK)
		src[0] = 'b';
	else if ((mode & S_IFMT) == S_IFDIR)
		src[0] = 'd';
	else if ((mode & S_IFMT) == S_IFCHR)
		src[0] = 'c';
	else if ((mode & S_IFMT) == S_IFIFO)
		src[0] = 'p';
	i = 0;
	while (++i < 10)
		src[i] = (mode & (1 << (9 - i))) ? str[i - 1] : '-';
	src[10] = '\0';

	// acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	// if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	// {
	// 	acl_free(acl);
	// 	acl = NULL;
	// }
	// if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 0)
	// 	src[10] = '@';
	// else if (acl != NULL)
	// 	src[10] = '+';
	// src[11] = '\0';
}

void	ft_flag_p_f(mode_t mode, size_t flag, char type[2])
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
		// else if ((mode & S_IFMT) == S_IFDIR)
		// 	type[0] = '/';
		// else if ((mode & S_IFMT) == S_IFBLK)
		// 	type[0] = '\0';
		// else if ((mode & S_IFMT) == S_IFCHR)
		// 	type[0] = '\0';
		else if ((mode & S_IFMT) == S_IFIFO)
			type[0] = '|';
		else if (mode & S_IXUSR)
			type[0] = '*';

		//// % whiteout ?????????????????????
	}
	type[1] = '\0';
}

void	ft_print_data(t_ls *ls, t_lf *file)
{
	char	mode[12];
	char	type[2];
	char	link[256];
	char	date[13];
	size_t	len;

	len = 0;
	if (ls->flag & LMIN)
	{
		ft_str_mode(mode, file->st.st_mode);
		ft_printf("%s%c %*d %*s%*.*s  %*s %s ", mode, ' '
			, ls->size_link, file->st.st_nlink, ls->size_user, file->user
			, (ls->size_grp + 2) * ((ls->flag & OMIN) == 0), ls->size_grp * ((ls->flag & OMIN) == 0)
			, file->grp, ls->size_size, file->size, file->date);
		if (ls->flag & LMIN && (file->st.st_mode & S_IFMT) == S_IFLNK)
		{
			if ((len = readlink(file->pathname, link, 256)) < 0)
				ft_exit(3, 0);
		}
	}
	ft_flag_p_f(file->st.st_mode, ls->flag, type);
	link[len] = '\0';
	ft_printf("%s%.*s%.*s%.*s\n", file->name, type[0] != 0, type, 4 * (len > 0), " -> ", len, link);
}

void	ft_affich(t_ls *ls)
{
	size_t	i;

	i = 0;
	if (ls->flag & SMAJ)
		ft_select_sort(ls, &ft_less_s_maj_cmp);
	else if (ls->flag & TMIN)
		ft_select_sort(ls, &ft_less_t_cmp);
	else
		ft_select_sort(ls, &ft_ascii_cmp);
	if (ls->nb_elem && (ls->flag & SMIN || ls->flag & LMIN))
		ft_printf("total %zu\n", ls->total_block);
	while (i < ls->nb_elem)
	{

		if (ls->flag & SMIN)
			ft_printf("%*zu ", ls->size_block, ls->file[i]->st.st_blocks);
		ft_print_data(ls, ls->file[i]);
		i++;
	}
	if (!(ls->flag & DMIN) && ls->flag & RMAJ)
		ft_recursif(ls);
	ft_free_ls(ls);
}
