#include "include/ft_ls.h"

void	ft_affich(t_ls *ls)
{
	int i;

	i = 0;
	// printf("size = %d\n", ls->size);
	while (i < ls->size)
	{
		ft_printf("%s\n", ls->lf[i++].name);
	}
}