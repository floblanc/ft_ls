/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:17:43 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/27 17:42:58 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

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
	else if (mode == 3)
		ft_printf("Error while readlink\n");
	exit(mode);
}

int		ft_read_dir(t_ls *ls, char *path, int size)
{
	DIR		*rep;
	struct	dirent *dir;

	if (!(ls->file = (t_lf**)ft_memalloc(sizeof(t_lf*) * (size_t)(size + 1))))
		ft_exit(2, 0);
	ls->current_path = path;
	if ((rep = opendir(ls->current_path)) == NULL)
		perror("perror ft_read_dir -> ft_ls ");
	else
	{
		while ((dir = readdir(rep)) != NULL)
		{
			if (dir->d_name[0] != '.' || ls->flag & AMIN || (ls->flag & AMAJ
				&& ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, "..")))
			{
				if (!(ls->file[ls->nb_elem] = (t_lf*)ft_memalloc(sizeof(t_lf)))
					|| !(ls->file[ls->nb_elem]->name = ft_strdup(dir->d_name)))
					ft_exit(2, 0);
				ls->file[ls->nb_elem]->pathname = ft_create_path(ls->current_path, dir->d_name);
				ls->nb_elem++;
			}
		}
		closedir(rep);
	}
	ft_long_format(ls);
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
		if (lstat(*ls.to_read, &st) == -1)
			perror("perror main -> ft_ls ");
		else if (st.st_mode & S_IFDIR && !(ls.flag & DMIN))
			ft_read_dir(&ls, *ls.to_read, st.st_nlink);
		else
		{
			if (!(ls.file = (t_lf**)ft_memalloc(sizeof(t_lf*) * 2))
				|| !(ls.file[ls.nb_elem] = (t_lf*)malloc(sizeof(t_lf)))
				|| !(ls.file[ls.nb_elem]->name = ft_strdup(*ls.to_read)))
				ft_exit(2, 0);
			ls.current_path = ft_strdup("");
			ls.file[ls.nb_elem++]->pathname = ft_create_path(ls.current_path, *ls.to_read);
			printf("ok\n");
			ft_long_format(&ls);
		}
		free(*ls.to_read);
		ls.to_read++;
	}
	return (0);
}


// /Users/AntoinePouchet/Library/Application\ Support/Skype/astas13/media_messaging/emo_cache_v2






