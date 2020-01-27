/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 18:07:21 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static char	*ft_less_h_min(char *letters, char *ret, int i, int size)
{
	double tmp;

	tmp = (double)size;
	while (tmp / 1024 >= 1)
	{
		tmp /= 1024;
		i++;
	}
	size = ((int)(tmp * 100) % 10 < 5 ? (int)(tmp * 10) : (int)(tmp * 10) + 1);
	if (tmp >= 10)
	{
		if (!(ret = ft_itoa(size)))
			ft_exit(2, 0);
		ret[ft_strlen(ret) - 1] = letters[i];
	}
	else
	{
		if (!(ret = (char*)ft_memalloc(5)))
			ft_exit(2, 0);
		ret[0] = (char)((size / 10) + '0');
		ret[1] = (size % 10 ? '.' : letters[i]);
		ret[2] = (size % 10 ? (size % 10) + '0' : 0);
		ret[3] = (size % 10 ? letters[i] : 0);
	}
	return (ret);
}

static char	*ft_get_size(size_t size, size_t flag)
{
	char	*ret = NULL;

	if (flag & HMIN && flag & LMIN)
		return (ft_less_h_min("BKMGTPE", ret, 0, (int)size));
	if (!(ret = ft_ulltoa(size)))
		ft_exit(2, 0);
	return (ret);
}

static char	*ft_get_date(time_t date)
{
	time_t	now;
	double	diff;
	char	*ret = NULL;
	char	*tmp = NULL;

	printf("start get date\n");
	diff = difftime(date, time(&now));
	printf("diff ?\n");
	printf("date = %ld\n", date);
	tmp = ctime(&date);
	printf("ctime ok\n");
	printf("tmp = %s\n", tmp);
	if (!(ret = ft_strdup(&tmp[4])))
		ft_exit(2, 0);
	printf("strdup ok\n");
	if (!(diff <= 0 && diff > -15552000))
		ft_strcpy(&(ret[7]), &(ret[15]));
	printf("strcpy ok\n");
	ret[12] = 0;
	return (ret);
}

static void	ft_get_maxsize(t_ls *ls, t_lf *file)
{
	size_t tmp;

	if (ls->size_block < (size_t)file->st.st_blocks)
		ls->size_block = (size_t)file->st.st_blocks;
	ls->total_block += (size_t)file->st.st_blocks;
	if (ls->size_link < file->st.st_nlink)
		ls->size_link = file->st.st_nlink;
	if (ls->size_user < (tmp = ft_strlen(file->user)))
		ls->size_user = tmp;
	if ((ls->flag & OMIN) == 0)
		if (ls->size_grp < (tmp = ft_strlen(file->grp)))
			ls->size_grp = tmp;
	if ((file->st.st_mode & S_IFMT) == S_IFCHR
		|| (file->st.st_mode & S_IFMT) == S_IFBLK)
	{
		if (ls->size_major < (file->smajor = ft_nbrlen_unsigned(file->major)))
			ls->size_major = file->smajor;
		if (ls->size_minor < (file->sminor = ft_nbrlen_unsigned(file->minor)))
			ls->size_minor = file->sminor;
		tmp = file->smajor + file->sminor + 2;
	}
	else
		tmp = ft_strlen(file->size);
	if (ls->size_size < tmp)
		ls->size_size = tmp;
}

static void	ft_get_user_grp(t_ls *ls, t_lf *file)
{
	struct passwd	*user;
	struct group	*grp;

	if ((ls->flag & NMIN) == 0)
	{
		if ((user = getpwuid(file->st.st_uid)) != NULL)
			file->user =  ft_strdup(user->pw_name);
		if ((ls->flag & OMIN) == 0)
		{
			if ((grp = getgrgid(file->st.st_gid)) != NULL)
				file->grp =  ft_strdup(grp->gr_name);
		}
	}
	if ((ls->flag & OMIN) == 0 && file->grp == NULL)
		file->grp = ft_itoa((int)file->st.st_gid);
	if (file->user == NULL)
		file->user = ft_itoa((int)file->st.st_uid);
	file->major = (size_t)file->st.st_rdev >> 24;
	file->minor = (size_t)file->st.st_rdev & 0xFFFFFF;
	ft_get_maxsize(ls, file);
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
	printf("tmp = %s\n", tmp);
	return (tmp);
}

static void	ft_device_size(t_ls *ls)
{
	size_t	i;
	char	*nb = NULL;
	char	*tmp = NULL;

	i = 0;
	printf("-------------\n\n");
	while (i < ls->nb_elem)
	{
		if ((ls->file[i]->st.st_mode & S_IFMT) == S_IFCHR
			|| (ls->file[i]->st.st_mode & S_IFMT) == S_IFBLK)
		{
			printf("value : major = %zu - minor = %zu\n", ls->file[i]->major, ls->file[i]->minor);
			printf("max size : major = %zu - minor = %zu\n", ls->size_major, ls->size_minor);
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

int		ft_long_format(t_ls *ls)
{
	struct stat st;
	size_t		i;

	i = 0;
	// if (ls->flag & LMIN || ls->flag & SMIN || ls->flag & SMAJ || ls->flag & TMIN
	// 	|| ls->flag & FMAJ || ls->flag & PMIN || ls->flag & RMAJ)
	{
		while (i < ls->nb_elem)	
		{
			printf("get long for : %s\n", ls->file[i]->pathname);
			if (lstat(ls->file[i]->pathname, &st) == -1)
				perror("perror ft_long_format -> ft_ls ");
			else
			{
				ls->file[i]->st = st;
				ls->file[i]->date = ft_get_date(ls->file[i]->st.st_mtime);
				ls->file[i]->size = ft_get_size((size_t)ls->file[i]->st.st_size, ls->flag);
				ft_get_user_grp(ls, ls->file[i]);
				printf("get user/grp and size ok\n");
			}
			i++;
		}
		ls->size_block = ft_nbrlen_unsigned(ls->size_block);
		ls->size_link = ft_nbrlen_unsigned(ls->size_link);
		ft_device_size(ls);
	}
	ft_affich(ls);
	return (0);
}
