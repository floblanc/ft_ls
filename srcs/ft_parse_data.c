/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 22:57:03 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/28 16:41:55 by apouchet         ###   ########.fr       */
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
	char	*ret;

	if (flag & HMIN && flag & LMIN)
		return (ft_less_h_min("BKMGTPE", ret, 0, (int)size));
	if (!(ret = ft_ulltoa(size)))
		ft_exit(2, 0);
	return (ret);
}

static char	*ft_get_date(t_lf *file, size_t *flag)
{
	time_t	now;
	time_t	date;
	double	diff;
	char	*ret;
	char	*tmp;

	if (*flag & CMIN)
		date = file->st.st_mtime;
	else if (*flag & UMIN)
		date = file->st.st_atime;
	else if (*flag & UMAJ)
		date = file->st.st_birthtime;
	diff = difftime(date, time(&now));
	tmp = ctime(&date);
	if (!(ret = ft_strdup(&tmp[4])))
		ft_exit(2, 0);
	if (!(diff <= 0 && diff > -15552000) && !(*flag & TMAJ))
		ft_strcpy(&(ret[7]), &(ret[15]));
	ret[(*flag & TMAJ ? 20 : 12)] = 0;
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
			ls->size_minor = (file->minor < 256 ? file->sminor : 0);
		tmp = file->smajor + (file->minor < 256 ? file->sminor : 0) + 4;
	}
	else
		tmp = ft_strlen(file->size);
	if (ls->size_size < tmp)
		ls->size_size = tmp;
}

void		ft_get_user_grp(t_ls *ls, struct stat st, t_lf *file)
{
	struct passwd	*user;
	struct group	*grp;

	file->st = st;
	file->date = ft_get_date(file, &(ls->flag));
	file->size = ft_get_size((size_t)file->st.st_size, ls->flag);
	if ((ls->flag & NMIN) == 0)
	{
		if ((user = getpwuid(file->st.st_uid)) != NULL)
			file->user = ft_strdup(user->pw_name);
		if ((ls->flag & OMIN) == 0)
			if ((grp = getgrgid(file->st.st_gid)) != NULL)
				file->grp = ft_strdup(grp->gr_name);
	}
	if ((ls->flag & OMIN) == 0 && file->grp == NULL)
		file->grp = ft_itoa((int)file->st.st_gid);
	if (file->user == NULL)
		file->user = ft_itoa((int)file->st.st_uid);
	file->major = (size_t)file->st.st_rdev >> 24;
	file->minor = (size_t)file->st.st_rdev & 0xFFFFFF;
	if (ls->size_ino < file->st.st_ino)
		ls->size_ino = file->st.st_ino;
	ft_get_maxsize(ls, file);
}
