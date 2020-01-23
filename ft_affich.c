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
