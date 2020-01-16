/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:17:43 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/16 18:17:50 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "include/ft_ls.h"

// struct dirent {
//     ino_t          d_ino;       /* numéro d'inœud */
//     off_t          d_off;       /* décalage jusqu'à la dirent suivante */
//     unsigned short d_reclen;    /* longueur de cet enregistrement */
//     unsigned char  d_type;      /* type du fichier */
//     char           d_name[256]; /* nom du fichier */
// };

void	ft_get_to_read(t_ls *ls, int size, int argc, char **argv)
{
	int i;
	int nb;

	i = 1;
	nb = 0;
	if (!(ls->to_read = (char**)malloc((sizeof(char*) * size + 1))))
	{
		printf("Error malloc\n");
		exit(0);
	}
	ls->to_read[size] = NULL;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			ls->to_read[nb++] = ft_strdup(argv[i]);
		i++;
	}
}

int		flag_stocker(char letter, int *flag)
{
	int	i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == letter)
		{
			*flags = *flags | ft_pow(2 ,i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_get_flag(t_ls *ls, int argc, char **argv)
{
	int i;
	int j;
	int	size;

	i = 1;
	size = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while(argv[i][j])
			{
				if (!(flag_stocker(argv[i][j], &(ls->flag))))
					ft_exit(1, argv[i][j]);
				j++;
			}
		}
		else
			size++;
		i++;
	}
	ft_get_to_read(ls, size, argc, argv);
}

int		main(int argc, char **argv)
{
	DIR		*rep;
	int		rd;
	struct dirent *dir;
	t_ls	ls;

	ls.flag = 0;
	// struct stat s;
	ft_get_flag(&ls, argc, argv);
	// if (*ls.to_read)
	// 	printf("%s:\n", *ls.to_read);
	while (*ls.to_read)
	{
		// printf("to read = %s\n", *ls.to_read);
		if ((rep = opendir(*ls.to_read)) == NULL)
			perror("ft_ls ");
		else
		{
			while ((dir = readdir(rep)) != NULL)
			{
				// printf("flag = %d - is -a : %d\n", ls.flag, (ls.flag & A));
				if (dir->d_name[0] != '.' || ls.flag & A)
				printf("%s\n", dir->d_name);
			}
			closedir(rep);
			ls.to_read++;
			if (*ls.to_read)
				printf("\n%s:\n", *ls.to_read);
		}
	}
	// if ((dir = readdir(rep)) == NULL)
		// perror("Error ");
	return (0);
}