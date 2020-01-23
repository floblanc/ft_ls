/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:17:43 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/23 15:38:26 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

// struct dirent {
//     ino_t          d_ino;       /* numéro d'inœud */
//     off_t          d_off;       /* décalage jusqu'à la dirent suivante */
//     unsigned short d_reclen;    /* longueur de cet enregistrement */
//     unsigned char  d_type;      /* type du fichier */
//     char           d_name[256]; /* nom du fichier */
// };

void	ft_exit(int mode, char c)
{
	if (mode == 1)
		ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [%s] [file ...]\n"
			, c, FLAGS);
	else if (mode == 2)
		ft_printf("Error malloc\n");
	exit(mode);
}

int		ft_long_format(t_ls *ls)
{
	struct stat st;
	if (ls->flag & LMIN)
	{
		;
	}
	ft_affich(ls);
	return (0);
}

int		ft_read_dir(t_ls *ls, char *path, int size)
{
	DIR		*rep;
	struct	dirent *dir;

	ls->size = 0;
	if (!(ls->file = (t_lf**)malloc(sizeof(t_lf*) * (size + 1))))
		ft_exit(2, 0);
	ls->file[size] = NULL;
	if ((rep = opendir(*ls->to_read)) == NULL)
		perror("ft_ls ");
	else
	{
		while ((dir = readdir(rep)) != NULL)
		{
			if (dir->d_name[0] != '.' || ls->flag & AMIN)
			{
				if (!(ls->file[ls->size] = (t_lf*)malloc(sizeof(t_lf))))
					ft_exit(2, 0);
				ls->file[ls->size++]->name = ft_strdup(dir->d_name);//to secure
			}
		}
		closedir(rep);
	}
	ft_long_format(ls);
	free(ls->file);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ls	ls;
	struct stat st;

	ft_bzero(&ls, sizeof(t_ls));
	ft_get_flag(&ls, argc, argv);
	while (*ls.to_read)
	{
		if (stat(*ls.to_read, &st) == -1)
			perror("ft_ls ");
		else if (st.st_mode & S_IFDIR)
			ft_read_dir(&ls, *ls.to_read, st.st_nlink);
		else
			printf("%s\n", *ls.to_read); // have to switch for affich function
		// printf("-----\nls.link = %d, ls.size = %lld\n",st.st_nlink, st.st_size);
		ls.to_read++;
	}
	return (0);
}
