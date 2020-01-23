#include "include/ft_ls.h"

int		ft_ascii_cmp(t_lf *f1, t_lf *f2)
{
	return ((ft_strcmp(f1->name, f2->name)) <= 0);
}

void	ft_bubble_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2))
{
	unsigned int	i;
	t_lf			*tmp;

	i = 1;
	while (i < ls->size)
	{
		if (!(cmp(ls->file[i - 1], ls->file[i])))
		{
			tmp = ls->file[i - 1];
			ls->file[i - 1] = ls->file[i];
			ls->file[i] = tmp;
			i = 0;
		}
		i++;
	}
}

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
			perror("ft_ls ");
		else if (st.st_mode & S_IFDIR)
		{
			ft_printf("\n%s:\n", path);
			ft_read_dir(&new_ls, path, st.st_nlink);
		}
		free(path);
		i++;
	}
}

void	ft_affich(t_ls *ls)
{
	int i;

	i = 0;
	ft_bubble_sort(ls, &ft_ascii_cmp);
	while (i < ls->size)
	{
		ft_printf("%s\n", ls->file[i++]->name);
	}
	if (ls->flag & RMAJ)
		ft_recursif(ls);
}
