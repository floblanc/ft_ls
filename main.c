/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:17:43 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/16 19:09:30 by apouchet         ###   ########.fr       */
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



int		ft_read_dir(t_ls *ls, char *path)
{
	DIR		*rep;
	struct	dirent *dir;

	if ((rep = opendir(*ls->to_read)) == NULL)
		perror("ft_ls ");
	else
	{
		while ((dir = readdir(rep)) != NULL)
			if (dir->d_name[0] != '.' || ls->flag & AMIN)
				printf("%s\n", dir->d_name);
		closedir(rep);
	}
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
			ft_read_dir(&ls, *ls.to_read);
		else
			printf("%s\n", *ls.to_read); // have to switch for print function
		ls.to_read++;
	}
	return (0);
}