/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:25:32 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/26 15:26:05 by apouchet         ###   ########.fr       */
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
	size = (unsigned int)tmp;
	if (tmp >= 10)
	{
		if (!(ret = ft_itoa((int)size)))
			ft_exit(2, 0);
		ret[ft_strlen(ret) - 2] = letters[i];
	}
	else
	{
		if (!(ret = (char*)ft_memalloc(5)))
			ft_exit(2, 0);
		ret[0] = (size / 10) + '0';
		ret[1] = '.';
		ret[2] = (size % 10) + '0';
		ret[3] = letters[i];
	}
	return (ret);
}

char	*ft_get_size(size_t size, int flag)
{
	char	*ret;
	if (flag & HMIN && flag & LMIN)
		return (ft_less_h_min("BKMGTPEZY", ret, 0, size));
	if (!(ret = ft_ulltoa(size)))
		ft_exit(2, 0);
	return (ret);
}

// void	ft_show_data(t_lf *lf)
// {
// 	printf("\nname : %s\n", lf->name);
// 	printf("lf->mode = %d\n", lf->mode);
// 	printf("lf->nb_link = %d\n", lf->nb_link);
// 	printf("lf->uid = %d\n", lf->uid);
// 	printf("lf->gid = %d\n", lf->gid);
// 	printf("lf->size = %lld\n", lf->file_size);
// 	printf("lf->mtime = %ld\n", lf->mtime);
// }

int		ft_long_format(t_ls *ls)
{
	struct stat st;
	size_t		i;

	i = 0;
	if (ls->flag & LMIN || ls->flag & SMIN || ls->flag & SMAJ || ls->flag & TMIN)
	{
		while (i < ls->nb_elem)	
		{
			if (lstat(ls->file[i]->pathname, &st) == -1)
				perror("perror ft_long_format -> ft_ls ");
			else
			{
				ls->file[i]->st = st;
				// printf("st_blksize = %d\n", st.st_blksize);
				// printf("st_blocks = %lld\n", ls->file[i]->st.st_blocks);
				if (ls->size_block < ls->file[i]->st.st_blocks)
					ls->size_block = ls->file[i]->st.st_blocks;
				ls->total_block += ls->file[i]->st.st_blocks;
				if (ls->size_link < ls->file[i]->st.st_nlink)
					ls->size_link = ls->file[i]->st.st_nlink;
				if (ls->size_size < ls->file[i]->st.st_size)
					ls->size_size = ls->file[i]->st.st_size;
				// ft_show_data(ls->file[i]);
			}
			i++;
		}
		ls->size_block = ft_nbrlen_unsigned(ls->size_block);
		ls->size_link = ft_nbrlen_unsigned(ls->size_link);
		ls->size_size = ft_nbrlen_unsigned(ls->size_size);
	}
	ft_affich(ls);
	return (0);
}