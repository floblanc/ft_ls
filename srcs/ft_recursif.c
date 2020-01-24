/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:26:03 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/24 15:56:02 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	*ft_create_path(char *path, char *file)
{
	char	*new;
	int		size;

	size = ft_strlen(path) + ft_strlen(file) + 2;
	if (!(new = (char*)ft_memalloc(sizeof(char) * size)))
		ft_exit(2, 0);
	new = ft_strcat(new, path);
	new = ft_strcat(new, "/");
	new = ft_strcat(new, file);
	return (new);
}


void	ft_recursif(t_ls *ls)
{
	t_ls	new_ls;
	int		i;
	char	*path;
	struct	stat st;

	i = 0;
	while (i < ls->size)
	{
		ft_bzero(&new_ls, sizeof(t_ls));
		new_ls.flag = ls->flag;
		path = ft_create_path(ls->current_path, ls->file[i]->name);
		if (stat(path, &st) == -1)
			perror("perror ft_recursif -> ft_ls ");
		else if (st.st_mode & S_IFDIR)
		{
			ft_printf("\n%s:\n", path);
			ft_read_dir(&new_ls, path, st.st_nlink);
		}
		free(path);
		i++;
	}
}
