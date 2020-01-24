/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:17:43 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/24 17:39:35 by apouchet         ###   ########.fr       */
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
	exit(mode);
}

void	ft_show_data(t_lf *lf)
{
	printf("\nname : %s\n", lf->name);
	printf("lf->mode = %d\n", lf->mode);
	printf("lf->nb_link = %d\n", lf->nb_link);
	printf("lf->uid = %d\n", lf->uid);
	printf("lf->gid = %d\n", lf->gid);
	printf("lf->size = %lld\n", lf->file_size);
	printf("lf->mtime = %ld\n", lf->mtime);
}

int		ft_long_format(t_ls *ls)
{
	struct stat st;
	size_t		i;

	i = 0;
	dprintf(2, "\nstart ft_long_format\n");
	dprintf(2, "i = %zu - ls->size = %zu\n\n", i, ls->size);
	while (i < ls->size)	
	{
		dprintf(2, "i : %zu\n", i);
		dprintf(2, "name : %s\n", ls->file[i]->name);
		dprintf(2, "path : %s\n", ls->file[i]->pathname);
		if (lstat(ls->file[i]->pathname, &st) == -1)
		{
			dprintf(2, "a\n");
			printf("--- %s ---\n", ls->file[i]->name);
			perror("perror ft_long_format -> ft_ls ");
		}
		else
		{
			dprintf(2, "b\n");
			ls->file[i]->mode = st.st_mode;
			ls->file[i]->nb_link = st.st_nlink;
			ls->file[i]->uid = st.st_uid;
			ls->file[i]->gid = st.st_gid;
			ls->file[i]->file_size = st.st_size;
			ls->file[i]->mtime = st.st_mtime;
			// ft_show_data(ls->file[i]);
		}
		i++;
	}
	ft_affich(ls);
	return (0);
}

int		ft_read_dir(t_ls *ls, char *path, int size)
{
	DIR		*rep;
	struct	dirent *dir;

	if (!(ls->file = (t_lf**)ft_memalloc(sizeof(t_lf*) * (size + 1))))
		ft_exit(2, 0);
	ls->current_path = path;
	if ((rep = opendir(ls->current_path)) == NULL)
		perror("perror ft_read_dir -> ft_ls ");
	else
	{
		while ((dir = readdir(rep)) != NULL)
		{
			// dprintf(2, "1\n");
			if (dir->d_name[0] != '.' || ls->flag & AMIN)
			{
				// dprintf(2, "2\n");
				if (!(ls->file[ls->size] = (t_lf*)ft_memalloc(sizeof(t_lf)))
					|| !(ls->file[ls->size]->name = ft_strdup(dir->d_name)))
					ft_exit(2, 0);
				// dprintf(2, "3\n");
				ls->file[ls->size]->pathname = ft_create_path(ls->current_path, dir->d_name);
				ls->size++;
				dprintf(2, "4\n");
				dprintf(2, "name : %s\n", ls->file[ls->size - 1]->name);
				dprintf(2, "path : %s\n", ls->file[ls->size - 1]->pathname);
				dprintf(2, "size : %zu\n", ls->size - 1);
				dprintf(2, "\n");
				int i = 0;
				while (i < ls->size)
				{
					dprintf(2, "i = %d\n", i);
					dprintf(2, "name : %s\n", ls->file[i]->name);
					dprintf(2, "path : %s\n", ls->file[i]->pathname);
					i++;
				}
			}
		}
		printf("end while\n");
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
		printf("new file : %s\n", *ls.to_read);
		if (lstat(*ls.to_read, &st) == -1)
			perror("perror main -> ft_ls ");
		else if (st.st_mode & S_IFDIR)
			ft_read_dir(&ls, *ls.to_read, st.st_nlink);
		else
		{
			if (!(ls.file = (t_lf**)ft_memalloc(sizeof(t_lf*) * 2))
				|| !(ls.file[ls.size] = (t_lf*)malloc(sizeof(t_lf)))
				|| !(ls.file[ls.size]->name = ft_strdup(*ls.to_read)))
				ft_exit(2, 0);
			ls.current_path = ft_strdup(".");
			ls.file[ls.size++]->pathname = ft_create_path(ls.current_path, *ls.to_read);
			ft_long_format(&ls);
		}
		printf("--- tour ---\n");
		ls.to_read++;
	}
	return (0);
}
