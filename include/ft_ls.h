/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:22:40 by floblanc          #+#    #+#             */
/*   Updated: 2020/02/03 17:13:13 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/include/libprintf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <errno.h>
# include <string.h>

# define AMAJ 0x00000001
# define FMAJ 0x00000002
# define RMAJ 0x00000004
# define SMAJ 0x00000008
# define TMAJ 0x00000010
# define UMAJ 0x00000020
# define AMIN 0x00000040
# define CMIN 0x00000080
# define DMIN 0x00000100
# define FMIN 0x00000200
# define GMIN 0x00000400
# define HMIN 0x00000800
# define IMIN 0x00001000
# define LMIN 0x00002000
# define MMIN 0x00004000
# define NMIN 0x00008000
# define OMIN 0x00010000
# define PMIN 0x00020000
# define RMIN 0x00040000
# define SMIN 0x00080000
# define TMIN 0x00100000
# define UMIN 0x00200000
# define FLAGS "AFRSTUacdfghilmnoprstu"

typedef struct	s_lf
{
	char		*pathname;
	char		*name;
	char		*date;
	char		*user;
	char		*grp;
	char		*size;
	struct stat	st;
	size_t		smajor;
	size_t		sminor;
	size_t		major;
	size_t		minor;
}				t_lf;

typedef struct	s_ls
{
	size_t		flag;
	size_t		nb_file;
	size_t		nb_dir;
	char		*current_path;
	char		**dir_read;
	char		**file_read;
	t_lf		**file;
	size_t		nb_elem;
	size_t		size_ino;
	size_t		size_block;
	size_t		size_link;
	size_t		size_user;
	size_t		size_grp;
	size_t		size_size;
	size_t		size_major;
	size_t		size_minor;
	size_t		total_block;

}				t_ls;

void			ft_read_dir(t_ls *ls, char *path, int size);

void			ft_get_flag(t_ls *ls, int argc, char **argv);

void			ft_exit(int mode, char c);

void			ft_affich(t_ls *ls, int mode);

int				ft_ascii_cmp(t_lf *f1, t_lf *f2, size_t *flag);

int				ft_less_s_maj_cmp(t_lf *f1, t_lf *f2, size_t *flag);

int				ft_less_t_cmp(t_lf *f1, t_lf *f2, size_t *flag);

char			*ft_create_path(char *path, char *file);

void			ft_recursif(t_ls *ls);

void			ft_long_format(t_ls *ls, int mode);

size_t			ft_dir_size(char *path);

void			ft_get_user_grp(t_ls *ls, struct stat st, t_lf *file);

void			ft_str_mode(char src[12], mode_t mode, char *pathname
	, t_lf *file);

void			ft_select_sort(t_ls *ls, int (*cmp)(t_lf *f1, t_lf *f2
	, size_t *f));

void			ft_new_file(t_ls *ls, char *name);

void			ft_free_ls(t_ls *ls);

#endif
