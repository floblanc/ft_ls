/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 23:33:11 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void ft_acl(char src[12], char *pathname)
{
	acl_t		acl = NULL;
	acl_entry_t	dummy;

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

void	ft_str_mode(char src[12], mode_t mode, char *pathname)
{
	static char	str[] = "rwxrwxrwx";
	int			i;
	mode_t		tmp;

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
	i = 0;
	while (++i < 10)
		src[i] = (mode & (1 << (9 - i))) ? str[i - 1] : '-';
	src[10] = ' ';
	ft_acl(src, pathname);
}

static char	*ft_device_minor_size(t_ls *ls, t_lf *file, char *tmp, char *nb)
{
	size_t j;
	size_t size;

	tmp[ls->size_major + ls->size_minor - file->sminor + 2] = 0;
	if (!(nb = ft_itoa_unsigned_base(file->minor
		, (file->minor < 200 ? 10 : 16), 0)))
			ft_exit(2, 0);
	if (file->minor >= 200)
	{
		size = ft_strlen(nb);
		j = ft_strlen(tmp);
		tmp[j++] = '0';
		tmp[j++] = 'x';
		while (size++ < 8)
			tmp[j++] = '0';
		tmp[j] = 0;
	}
	tmp = ft_strcat(tmp, nb);
	free(nb);
	// printf("tmp = %s\n", tmp);
	return (tmp);
}

static void	ft_device_size(t_ls *ls)
{
	size_t	i;
	char	*nb = NULL;
	char	*tmp = NULL;

	i = 0;
	// printf("-------------\n\n");
	while (i < ls->nb_elem)
	{
		if ((ls->file[i]->st.st_mode & S_IFMT) == S_IFCHR
			|| (ls->file[i]->st.st_mode & S_IFMT) == S_IFBLK)
		{
			// printf("value : major = %zu - minor = %zu\n", ls->file[i]->major, ls->file[i]->minor);
			// printf("max size : major = %zu - minor = %zu\n", ls->size_major, ls->size_minor);
			if (!(tmp = (char*)malloc(ls->size_major + ls->size_minor + 13))
				|| !(nb = ft_itoa_unsigned(ls->file[i]->major)))
				ft_exit(2, 0);
			tmp = ft_memset(tmp, ' ', ls->size_major + ls->size_minor + 10);
			tmp = ft_strcpy(&tmp[ls->size_major - ls->file[i]->smajor], nb);
			tmp[ls->size_major] = ',';
			free(nb);
			ls->file[i]->size = ft_device_minor_size(ls, ls->file[i], tmp, nb);
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
		ft_device_size(ls);
	}
	ft_affich(ls);
}
