/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/02/05 20:18:29 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	ft_acl(char src[12], char *pathname, mode_t mode, t_lf *file)
{
	acl_t		acl;
	acl_entry_t	dummy;

	acl = NULL;
	if ((file->st.st_mode & S_ISUID))
		src[3] = ((mode & (1 << 6)) != 0 ? 's' : 'S');
	else if ((file->st.st_mode & S_ISGID))
		src[6] = ((mode & (1 << 3)) != 0 ? 's' : 'S');
	else if ((file->st.st_mode & S_ISVTX))
		src[9] = ((mode & 1) != 0 ? 't' : 'T');
	acl = acl_get_link_np(pathname, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(&acl);
		acl = NULL;
	}
	if (listxattr(pathname, NULL, 0, XATTR_NOFOLLOW) > 0)
		src[10] = '@';
	else if (acl)
		src[10] = '+';
	if (acl)
		free(acl);
	src[11] = '\0';
}

void		ft_str_mode(char src[12], mode_t mode, char *pathname, t_lf *file)
{
	mode_t		tmp;
	static char	str[] = "rwxrwxrwx";
	size_t		i;

	i = 0;
	tmp = mode & S_IFMT;
	if (tmp == S_IFSOCK)
		src[0] = 's';
	else if (tmp == S_IFLNK)
		src[0] = 'l';
	else if (tmp == S_IFREG)
		src[0] = '-';
	else if (tmp == S_IFBLK)
		src[0] = 'b';
	else if (tmp == S_IFDIR)
		src[0] = 'd';
	else if (tmp == S_IFCHR)
		src[0] = 'c';
	else if (tmp == S_IFIFO)
		src[0] = 'p';
	src[10] = ' ';
	while (++i < 10)
		src[i] = (mode & (1 << (9 - i))) ? str[i - 1] : '-';
	ft_acl(src, pathname, mode, file);
}

static char	*ft_device_minor_size(t_ls *ls, t_lf *file, char *tmp, char *nb)
{
	size_t	j;
	size_t	size;
	int		hex;

	hex = (file->minor >= 256 ? 1 : 0);
	if (hex)
		tmp[ls->size_major + hex + 2] = 0;
	else
		tmp[ls->size_major + ls->size_minor - file->sminor + 3 + hex] = 0;
	if (!(nb = ft_itoa_unsigned_base(file->minor, (hex ? 16 : 10), 0)))
		ft_exit(2, 0);
	if (hex == 1)
	{
		size = ft_strlen(nb);
		j = ft_strlen(tmp) + 0;
		tmp[j++] = '0';
		tmp[j++] = 'x';
		while (size++ < 8)
			tmp[j++] = '0';
		tmp[j] = 0;
	}
	tmp = ft_strcat(tmp, nb);
	free(nb);
	return (tmp);
}

static void	ft_device_size(t_ls *ls, size_t i)
{
	char	*nb;
	char	*tmp;
	int		hex;

	ls->size_block = ft_nbrlen_unsigned(ls->size_block);
	ls->size_link = ft_nbrlen_unsigned(ls->size_link);
	ls->size_ino = ft_nbrlen_unsigned(ls->size_ino);
	while (i < ls->nb_elem)
	{
		if ((ls->file[i]->st.st_mode & S_IFMT) == S_IFCHR
			|| (ls->file[i]->st.st_mode & S_IFMT) == S_IFBLK)
		{
			hex = (ls->file[i]->minor >= 256 ? 1 : 0);
			if (!(tmp = (char*)malloc(ls->size_major + ls->size_minor + 13))
				|| !(nb = ft_itoa_unsigned(ls->file[i]->major)))
				ft_exit(2, 0);
			tmp = ft_memset(tmp, ' ', ls->size_major + ls->size_minor + 10);
			tmp[ls->size_major - ls->file[i]->smajor + hex] = 0;
			tmp = ft_strcat(tmp, nb);
			tmp[ls->size_major + hex] = ',';
			free(nb);
			ls->file[i]->size = ft_device_minor_size(ls, ls->file[i], tmp, nb);
		}
		i++;
	}
}

void		ft_long_format(t_ls *ls, int mode)
{
	struct stat st;
	size_t		i;

	i = 0;
	if (ls->flag & LMIN || ls->flag & SMIN || ls->flag & SMAJ || ls->flag & TMIN
		|| ls->flag & FMAJ || ls->flag & PMIN || ls->flag & RMAJ)
	{
		while (i < ls->nb_elem)
		{
			if (lstat(ls->file[i]->pathname, &st) == -1)
				ft_printf("ft_ls: %s: %s\n"
					, ls->file[i++]->name, strerror(errno));
			else
				ft_get_user_grp(ls, st, ls->file[i++]);
		}
		ft_device_size(ls, 0);
	}
	if (ls->flag & SMAJ)
		ft_select_sort(ls, &ft_less_s_maj_cmp);
	else if (ls->flag & TMIN)
		ft_select_sort(ls, &ft_less_t_cmp);
	else
		ft_select_sort(ls, &ft_ascii_cmp);
	if (mode)
		ft_affich(ls, mode);
}
