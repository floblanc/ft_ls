/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:22:40 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/23 15:25:20 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

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
// # include "../libftprintf/include/libprintf.h"
#include "../libft/libft.h"

# define AMAJ 1
# define FMAJ 2
# define RMAJ 4
# define SMAJ 8
# define AMIN 16
# define DMIN 32
# define HMIN 64
# define LMIN 128
# define PMIN 256
# define RMIN 512
# define SMIN 1028
# define TMIN 2048
# define FLAGS "AFRSadhlprst"

typedef struct		s_lf
{
	char			*name;
	// char			name[256];
	unsigned char	type;
	// dev_t			st_dev;     /* ID of device containing file */
	// ino_t			st_ino;		/* inode number */
	// mode_t			st_mode;	/* protection */
	// nlink_t			st_nlink;	/* number of hard links */
	// uid_t			st_uid;		/* user ID of owner */
	// gid_t			st_gid;		/* group ID of owner */
	// dev_t			st_rdev;	/* device ID (if special file) */
	// off_t			st_size;	/* total size, in bytes */
	// blksize_t		st_blksize;	/* blocksize for file system I/O */
	// blkcnt_t			st_blocks;	/* number of 512B blocks allocated */
	// time_t			st_atime;	/* time of last access */
	// time_t			st_mtime;	/* time of last modification */
	// time_t			st_ctime;	/* time of last status change */
}					t_lf;

typedef struct		s_ls
{
	int				flag;
	char			**to_read;
	int				size;
	t_lf			**file;
}					t_ls;

void	ft_get_flag(t_ls *ls, int argc, char **argv);

void	ft_exit(int mode, char c);

void	ft_affich(t_ls *ls);

#endif
