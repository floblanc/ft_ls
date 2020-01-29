/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:17:43 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/29 16:12:31 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		ft_exit(int mode, char c)
{
	if (mode == 1)
		ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n"
			, c, FLAGS);
	else if (mode == 2)
		ft_printf("Error malloc\n");
	else if (mode == 3)
		ft_printf("Error while readlink\n");
	exit(mode);
}

void		ft_new_file(t_ls *ls, char *name)
{
	t_lf	**tmp;
	size_t	i;

	i = 0;
	if (!(ls->file[ls->nb_elem] = (t_lf*)ft_memalloc(sizeof(t_lf)))
		|| !(ls->file[ls->nb_elem]->name = ft_strdup(name)))
		ft_exit(2, 0);
	ls->file[ls->nb_elem]->pathname = ft_create_path(ls->current_path, name);
	ls->nb_elem++;
}

void		ft_read_dir(t_ls *ls, char *path, int size)
{
	DIR				*rep;
	struct dirent	*dir;

	if (!(ls->file = (t_lf**)ft_memalloc(sizeof(t_lf*) * (size_t)(size + 1))))
		ft_exit(2, 0);
	ls->current_path = path;
	if ((rep = opendir(ls->current_path)) == NULL)
		ft_printf("ft_ls: %s: %s\n", ls->current_path, strerror(errno));
	else
	{
		while ((dir = readdir(rep)) != NULL)
		{
			if (dir->d_name[0] != '.' || ls->flag & AMIN || (ls->flag & AMAJ
				&& ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, "..")))
				ft_new_file(ls, dir->d_name);
		}
		closedir(rep);
	}
	ft_long_format(ls, 1);
}

void		ft_read_file(t_ls *ls)
{
	size_t i;

	i = 0;
	if (ls->nb_file)
	{
		if (!(ls->current_path = ft_strdup("."))
			|| !(ls->file = (t_lf**)ft_memalloc(8 * (size_t)(ls->nb_file + 1))))
			ft_exit(2, 0);
		while (ls->file_read[i])
		{
			ft_new_file(ls, ls->file_read[i]);
			free(ls->file_read[i++]);
		}
		ft_long_format(ls, 2);
		free(ls->file_read);
	}
}

int			main(int argc, char **argv)
{
	t_ls		ls;
	size_t		i;

	i = 0;
	ft_get_flag(&ls, argc, argv);
	ft_read_file(&ls);
	while (ls.dir_read[i])
	{
		if (ls.nb_file > 0 || i > 0 || ls.dir_read[i + 1])
			ft_printf("\n%s:\n", ls.dir_read[i]);
		ft_read_dir(&ls, ls.dir_read[i], ft_dir_size(ls.dir_read[i]));
		free(ls.dir_read[i++]);
	}
	free(ls.dir_read);
	return (0);
}
