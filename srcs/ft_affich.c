/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affich.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:28:17 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/26 17:25:58 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	ft_free_ls(t_ls *ls)
{
	size_t i;

	i = 0;
	while (i < ls->nb_elem)
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
	ls->nb_elem = 0;
	// printf("end free\n");
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

void	ft_str_date(char date[13])
{
	return ;
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

#include <sys/acl.h>

void	ft_str_mode(char src[12], mode_t mode)
{
	static char	str[] = "rwxrwxrwx";
	int			i;
	acl_t		acl = NULL;

	// printf("\n%#o\n", mode);

	if ((mode & S_IFMT) == S_IFLNK)
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

// char	ft_flag_p_f(t_mode mode, size_t flag)
// {
	// if ((mode & S_IFMT) == S_IFLNK)
	// 	src[0] = 'l';
	// else if ((mode & S_IFMT) == S_IFREG)
	// 	src[0] = '-';
	// else if ((mode & S_IFMT) == S_IFBLK)
	// 	src[0] = 'b';
	// else if ((mode & S_IFMT) == S_IFDIR)
	// 	src[0] = 'd';
	// else if ((mode & S_IFMT) == S_IFCHR)
	// 	src[0] = 'c';
	// else if ((mode & S_IFMT) == S_IFIFO)
	// 	src[0] = 'p';
// }

void	ft_affich(t_ls *ls)
{
	int i;
	char	mode[12];
	char	*user;
	char	*grp;
	char	date[13];
	char	link[256];
	size_t	len;

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
		len = 0;
		// if (ls->flag & SMIN)
		// 	ft_printf("%*zu ", ls->size_block, ls->file[i]->st.st_blocks);
		// if (ls->flag & LMIN)
		// {
		// 	ft_str_mode(mode, ls->file[i]->st.st_mode);
		// 	ft_printf("%s%c %*d %*s%*.*s  %*d %s ", mode, ' '
		// 		, ls->size_link, ls->file[i]->st.st_nlink, 8, "apouchet"
		// 		, (10 + 2) * ((ls->flag & OMIN) == 0), 10 * ((ls->flag & OMIN) == 0)
		// 		, "2016_paris", ls->size_size, ls->file[i]->st.st_size, "date");
		// 	// printf("%s\n", );
		// }
		if (ls->flag & LMIN && (ls->file[i]->st.st_mode & S_IFMT) == S_IFLNK)
		{
			if ((len = readlink(ls->file[i]->pathname, link, 256)) < 0)
				ft_exit(3, 0);
		}
		link[len] = '\0';
		printf("%s%s%.*s%.*s\n", ls->file[i]->name, 'a',4 * (len > 0), " -> ", len, link);
		i++;
	}
	if (!(ls->flag & DMIN) && ls->flag & RMAJ)
		ft_recursif(ls);
	ft_free_ls(ls);
}
