/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:26:03 by apouchet          #+#    #+#             */
/*   Updated: 2020/02/22 10:48:50 by floblanc         ###   ########.fr       */
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
	if (file[0] == '/')
		return (ft_strdup(file));
	size_a = ft_strlen(path);
	size_b = ft_strlen(file);
	if (!(new = (char*)malloc(sizeof(char) * (size_a + size_b + 2))))
		ft_exit(2, 0);
	j = 0;
	while (j < size_a)
		new[i++] = path[j++];
	if (file[0] != '/' && path[size_a - 1] != '/')
		new[i++] = '/';
	j = 0;
	while (j < size_b)
		new[i++] = file[j++];
	new[i] = '\0';
	return (new);
}

size_t	ft_dir_size(char *path)
{
	size_t			size;
	DIR				*rep;
	struct dirent	*dir;

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
