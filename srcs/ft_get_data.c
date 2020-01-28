/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/28 16:55:54 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void ft_acl(char src[12], char *pathname,  mode_t mode, t_lf *file)
{
	acl_t		acl = NULL;
	acl_entry_t	dummy;

	if ((file->st.st_mode & S_ISUID))
		src[3] = ((mode & (1 << 6)) != 0 ? 's' : 'S');
	else if ((file->st.st_mode & S_ISGID))
		src[6] = ((mode & (1 << 3)) != 0 ? 's' : 'S');
	else if ((file->st.st_mode & S_ISVTX))
		src[9] = ((mode & 1) != 0 ? 't' : 'T');
	acl = acl_get_link_np(pathname, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (listxattr(pathname, NULL, 0, XATTR_NOFOLLOW) > 0)
		src[10] = '@';
	else if (acl != NULL)
		src[10] = '+';
	src[11] = '\0';
}

void	ft_str_mode(char src[12], mode_t mode, char *pathname, t_lf *file)
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
	size_t j;
	size_t size;
	int		hex;

	hex = (file->minor >= 256 ? 1 : 0);
	if (hex)
		tmp[ls->size_major + hex + 2] = 0;
	else
		tmp[ls->size_major + ls->size_minor - file->sminor + 3 + hex] = 0;
	// printf("3.5 - tmp = -|%s|-\n", tmp);
	if (!(nb = ft_itoa_unsigned_base(file->minor , (hex ? 16 : 10), 0)))
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
			// printf("4 - tmp = -|%s|-\n", tmp);
	tmp = ft_strcat(tmp, nb);
			// printf("5 - tmp = -|%s|-\n", tmp);
	free(nb);
	return (tmp);
}

static void	ft_device_size(t_ls *ls)
{
	size_t	i;
	char	*nb = NULL;
	char	*tmp = NULL;
	int		hex;

	i = 0;
	while (i < ls->nb_elem)
	{
		if ((ls->file[i]->st.st_mode & S_IFMT) == S_IFCHR
			|| (ls->file[i]->st.st_mode & S_IFMT) == S_IFBLK)
		{
			hex = (ls->file[i]->minor >= 256 ? 1 : 0);
			// printf("minor = %zu\n", ls->file[i]->minor);
			if (!(tmp = (char*)malloc(ls->size_major + ls->size_minor + 13))
				|| !(nb = ft_itoa_unsigned(ls->file[i]->major)))
				ft_exit(2, 0);
			tmp = ft_memset(tmp, ' ', ls->size_major + ls->size_minor + 10);
			tmp[ls->size_major - ls->file[i]->smajor + hex] = 0;
			// printf("1 - tmp = -|%s|- %zu + %d\n", tmp, ls->size_major - ls->file[i]->smajor, hex);
			tmp = ft_strcat(tmp, nb);
			tmp[ls->size_major + hex] = ',';
			// printf("2 - tmp = -|%s|-\n", tmp);
			// tmp[ls->size_major + hex + 2] = 0;
			// printf("3 - tmp = -|%s|-\n", tmp);
			free(nb);
			ls->file[i]->size = ft_device_minor_size(ls, ls->file[i], tmp, nb);
			// printf("\n");
		}
		i++;
	}
}

void	ft_long_format(t_ls *ls)
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
			{
				printf("get long for : %s\n", ls->file[i]->pathname);
				perror("perror ft_long_format -> ft_ls ");
			}
			else
				ft_get_user_grp(ls, st, ls->file[i]);
			i++;
		}
		ls->size_block = ft_nbrlen_unsigned(ls->size_block);
		ls->size_link = ft_nbrlen_unsigned(ls->size_link);
		ls->size_ino = ft_nbrlen_unsigned(ls->size_ino);
		ft_device_size(ls);
	}
	ft_affich(ls);
}
