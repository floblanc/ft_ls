/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:26:03 by apouchet          #+#    #+#             */
/*   Updated: 2020/01/25 14:20:05 by apouchet         ###   ########.fr       */
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
	if (!(new = (char*)malloc(sizeof(char) * (size_a + size_b))))
		ft_exit(2, 0);
	while (j < size_a)
		new[i++] = path[j++];
	new[i++] = '/';
	j = 0;
	while (j < size_b)
		new[i++] = file[j++];
	new[i] = '\0';
	// new = ft_strcat(new, path);
	// new = ft_strcat(new, "/");
	// new = ft_strcat(new, file);
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
		// if (lstat(path, &st) == -1)
		// {
		// 	printf("--- %s ---\n", ls->file[i]->name);
		// 	perror("perror ft_recursif -> ft_ls ");
		// }
		// else if (st.st_mode & S_IFDIR)
		if (ls->file[i]->mode & S_IFDIR)
		{
			ft_bzero(&new_ls, sizeof(t_ls));
			new_ls.flag = ls->flag;
			path = ft_create_path(ls->current_path, ls->file[i]->name);
			ft_printf("\n%s:\n", path);
			ft_read_dir(&new_ls, path, st.st_nlink);
			free(path);
		}
		i++;
	}
}
