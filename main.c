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
				if (argv[i][j] == 'a')
					ls->flag = ls->flag | A;
				else if (argv[i][j] == 'l')
					ls->flag = ls->flag & L;
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
		{
			perror("ft_ls ");
			exit(0);
		}
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
	// if ((dir = readdir(rep)) == NULL)
		// perror("Error ");
	return (0);
}