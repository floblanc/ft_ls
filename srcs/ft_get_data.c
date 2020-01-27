/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 16:12:52 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	*ft_less_h_min(char *letters, char *ret, int i, size_t size)
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
		if (!(ret = ft_itoa((int)size)))
			ft_exit(2, 0);
		ret[ft_strlen(ret) - 1] = letters[i];
	}
	else
	{
		if (!(ret = (char*)ft_memalloc(5)))
			ft_exit(2, 0);
		ret[0] = (size / 10) + '0';
		ret[1] = (size % 10 ? '.' : letters[i]);
		ret[2] = (size % 10 ? (size % 10) + '0' : 0);
		ret[3] = (size % 10 ? letters[i] : 0);
	}
	return (ret);
}

char	*ft_get_size(size_t size, int flag)
{
	char	*ret;

	if (flag & HMIN && flag & LMIN)
		return (ft_less_h_min("BKMGTPE", ret, 0, size));
	if (!(ret = ft_ulltoa(size)))
		ft_exit(2, 0);
	return (ret);
}

char	*ft_get_date(time_t date)
{
	time_t	now;
	double	diff;
	char	*ret;
	char	*tmp;

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

void	ft_get_maxsize(t_ls *ls, t_lf *file)
{
	size_t tmp;
	size_t tmp_m;

	if (ls->size_block < file->st.st_blocks)
		ls->size_block = file->st.st_blocks;
	ls->total_block += file->st.st_blocks;
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

void	ft_get_user_grp(t_ls *ls, t_lf *file)
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
		file->grp = ft_itoa(file->st.st_gid);
	if (file->user == NULL)
		file->user = ft_itoa(file->st.st_uid);
	file->major = file->st.st_rdev >> 24;
	file->minor = file->st.st_rdev & 0xFFFFFF;
	ft_get_maxsize(ls, file);
}

void	ft_device_size(t_ls *ls)
{
	size_t	i;
	size_t	j;
	size_t	pos;
	char	*tmp;
	char	*nb;

	i = 0;
	printf("-------------\n\n");
	while (i < ls->nb_elem)
	{
		if ((ls->file[i]->st.st_mode & S_IFMT) == S_IFCHR
			|| (ls->file[i]->st.st_mode & S_IFMT) == S_IFBLK)
		{
			// printf("value : major = %d - minor = %d\n", ls->file[i]->major, ls->file[i]->minor);
			// printf("max size : major = %zu - minor = %zu\n", ls->size_major, ls->size_minor);
			if (!(tmp = (char*)malloc(ls->size_major + ls->size_minor + 13))
				|| !(nb = ft_itoa(ls->file[i]->major)))
				ft_exit(2, 0);
			tmp = ft_memset(tmp, ' ', ls->size_major + ls->size_minor + 10);
			j = 0;
			pos = ls->size_major - ls->file[i]->smajor;
			while (nb[j])
			{
				tmp[pos + j] = nb[j];
				j++;
			}
			tmp[pos + j++] = ',';
			// printf("major = %s\n", nb);
			free(nb);
			pos =  j + ls->size_minor - ls->file[i]->sminor + 1;
			j = 0;
			if (!(nb = ft_itoa(ls->file[i]->minor)))
				
				ft_exit(2, 0);
			while (nb[j])
			{
				tmp[pos + j] = nb[j];
				j++;
			}
			// printf("minor = %s\n", nb);
			tmp[pos + j] = 0;
			free(nb);
			printf("tmp = %s\n", tmp);
			ls->file[i]->size = tmp;
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
				// printf("data read st\n");
				ls->file[i]->st = st;
				// printf("dev = %d\n", ls->file[i]->st.st_rdev);
				// printf("major = %d, minor = %d\n", ls->file[i]->st.st_rdev >> 24, ls->file[i]->st.st_rdev & 0xFFFFFF);
				// printf("copie ok\n");
				// printf("ls->file[i]->st.st_mtime = %zu\n", ls->file[i]->st.st_mtime);
				ls->file[i]->date = ft_get_date(ls->file[i]->st.st_mtime);
				// printf("date ok\n");
				ls->file[i]->size = ft_get_size(ls->file[i]->st.st_size, ls->flag);
				// printf("size ok\n");
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