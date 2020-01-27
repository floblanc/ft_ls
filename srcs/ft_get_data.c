/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/27 12:43:44 by apouchet         ###   ########.fr       */
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

	diff = difftime(date, time(&now));
	if (!(ret = ft_strdup(&(ctime(&date)[4]))))
		ft_exit(2, 0);
	if (!(diff <= 0 && diff > -15552000))
		ft_strcpy(&(ret[7]), &(ret[15]));
	ret[12] = 0;
	return (ret);
}

void	ft_get_maxsize(t_ls *ls, t_lf *file)
{
	size_t tmp;

	if (ls->size_block < file->st.st_blocks)
		ls->size_block = file->st.st_blocks;
	ls->total_block += file->st.st_blocks;
	if (ls->size_link < file->st.st_nlink)
		ls->size_link = file->st.st_nlink;
	tmp = ft_strlen(file->user);
	if (ls->size_user < tmp)
		ls->size_user = tmp;
	if ((ls->flag & OMIN) == 0)
	{
		tmp = ft_strlen(file->grp);
		if (ls->size_grp < tmp)
			ls->size_grp = tmp;
	}
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
	ft_get_maxsize(ls, file);
}

int		ft_long_format(t_ls *ls)
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
				perror("perror ft_long_format -> ft_ls ");
			else
			{
				ls->file[i]->st = st;
				ls->file[i]->date = ft_get_date(ls->file[i]->st.st_mtime);
				ls->file[i]->size = ft_get_size(ls->file[i]->st.st_size, ls->flag);
				ft_get_user_grp(ls, ls->file[i]);
			}
			i++;
		}
		ls->size_block = ft_nbrlen_unsigned(ls->size_block);
		ls->size_link = ft_nbrlen_unsigned(ls->size_link);
	}
	ft_affich(ls);
	return (0);
}