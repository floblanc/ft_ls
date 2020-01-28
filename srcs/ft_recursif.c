/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:26:03 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/28 12:19:11 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	*ft_create_path(char *path, char *file)
{
	char	*new;
	size_t	size_a;
	size_t	size_b;
	size_t	i;
	size_t	j;

	i = 0;
	size_a = ft_strlen(path);
	size_b = ft_strlen(file);
	if (!(new = (char*)malloc(sizeof(char) * (size_a + size_b + 2))))
		ft_exit(2, 0);
	j = 0;
	while (j < size_a)
		new[i++] = path[j++];
	if (file[0] != '/')
		new[i++] = '/';
	j = 0;
	while (j < size_b)
		new[i++] = file[j++];
	new[i] = '\0';
	return (new);

	// char	*new;
	// size_t	size;

	// size = ft_strlen(path) + ft_strlen(file) + 2;
	// if (!(new = (char*)ft_memalloc(sizeof(char) * size)))
	// 	ft_exit(2, 0);
	// new = ft_strcat(new, path);
	// new = ft_strcat(new, "/");
	// new = ft_strcat(new, file);
	// // printf("new = %s\n", new);
	// return (new);
}

size_t	ft_dir_size(char *path)
{
	size_t size;
	DIR		*rep;
	struct	dirent *dir;

	size = 1;
	if ((rep = opendir(path)) != NULL)
	{
		while ((dir = readdir(rep)) != NULL)
			size++;
		closedir(rep);
	}
	return (size);
}

void	ft_recursif(t_ls *ls)
{
	t_ls	new_ls;
	size_t	i;
	char	*path;

	i = 0;
	while (i < ls->nb_elem)
	{
		// printf(". = %d, .. = %d, DIR = %d\n", ft_strcmp(ls->file[i]->name, "."), ft_strcmp(ls->file[i]->name, ".."), ls->file[i]->st.st_mode & S_IFDIR);
		if (ft_strcmp(ls->file[i]->name, ".")
			&& ft_strcmp(ls->file[i]->name, "..")
			&& (ls->file[i]->st.st_mode & S_IFMT) == S_IFDIR)
		{
			path = ft_create_path(ls->current_path, ls->file[i]->name);
			ft_bzero(&new_ls, sizeof(t_ls));
			new_ls.flag = ls->flag;
			ft_printf("\n%s:\n", path);
			ft_read_dir(&new_ls, path, ft_dir_size(path));
			free(path);
		}
		i++;
	}
}
