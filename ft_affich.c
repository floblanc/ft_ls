#include "include/ft_ls.h"

int		ft_ascii_cmp(t_lf *f1, t_lf *f2)
{
	return ((ft_strcmp(f1->name, f2->name)) <= 0);
}

int		ft_less_s_min_cmp(t_lf *f1, t_lf *f2)
{
	if (f1->st_size == f2->st_size)
		return (ft_ascii_cmp(f1, f2));
	return (f1->st_size < f2->st_size);
}

int		ft_less_t_cmp(t_lf *f1, t_lf *f2)
{
	double	diff;

	diff = difftime(f1->st_mtime, f2->st_mtime);
	if ((ssize_t)diff == 0)
		return (ft_ascii_cmp(f1, f2));
	return (diff < 0);
}

void	ft_bubble_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2))
{
	unsigned int	i;
	t_lf			*tmp;

	i = 1;
	while (i < ls->size)
	{
		// printf("%d == %d\n", (!(ls->flag & RMIN)), (cmp(ls->file[i - 1], ls->file[i])));
		if ((!(ls->flag & RMIN)) == !(cmp(ls->file[i - 1], ls->file[i])))
		{
			tmp = ls->file[i - 1];
			ls->file[i - 1] = ls->file[i];
			ls->file[i] = tmp;
			i = 0;
		}
		i++;
	}
}

void	ft_affich(t_ls *ls)
{
	int i;

	i = 0;
	ft_bubble_sort(ls, &ft_ascii_cmp);
	// printf("size = %d\n", ls->size);
	while (i < ls->size)
	{
		ft_printf("%s\n", ls->file[i++]->name);
	}
}
