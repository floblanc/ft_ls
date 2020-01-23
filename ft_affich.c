#include "include/ft_ls.h"

void	ft_affich(t_ls *ls)
{
	int i;

	i = 0;
	// printf("size = %d\n", ls->size);
	while (i < ls->size)
	{
		ft_printf("%s\n", ls->lf[i++]->name);
	}
}

void	ft_bubble sort(t_ls *ls, void (*cmp)(t_lf *f1, t_lf *f2))
{
	unsigned int	i;
	t_lf			*tmp;

	i = 1;
	while(i < size)
	{
		if (!(cmp(ls->lf[i - 1], ls->lf[i])))
		{
			tmp = ls->lf[i - 1];
			ls->lf[i - 1] = ls->lf[i];
			ls->lf[i] = tmp;
			i = 0;
		}
		i++;
	}
}