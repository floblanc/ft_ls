/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:22:40 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/27 12:51:21 by apouchet         ###   ########.fr       */
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
# define NMIN 256
# define OMIN 512
# define PMIN 1024
# define RMIN 2048
# define SMIN 4096
# define TMIN 8192
# define FLAGS "AFRSadhlnoprst"

// LMIN SMIN SMAJ TMIN FMAJ PMIN RMAJ

// to do F / l
typedef struct		s_lf
{
	char			*pathname;
	char			*name;
	unsigned char	type;

	// mode_t			mode;		/* protection */
	// nlink_t			nb_link;	/* number of hard links */
	// uid_t			uid;		 user ID of owner 
	// gid_t			gid;		/* group ID of owner */
	// off_t			file_size;	/* total size, in bytes */
	// time_t			mtime;		/* time of last modification */

	// char			*link;
	char			*date;
	char			*user;
	char			*grp;
	char			*size;
	struct stat 	st;

	
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

// char *ctime(const time_t *timer)
// example : Mon Aug 13 08:23:14 2012

// struct passwd *getpwuid(uid_t uid);
// struct passwd {
//     char   *pw_name;   /* Nom d'utilisateur */
//     char   *pw_passwd; /* Mot de passe de l'utilisateur */
//     uid_t   pw_uid;    /* Identifiant de l'utilisateur */
//     gid_t   pw_gid;    /* Identifiant du groupe de l'utilisateur */
//     char   *pw_gecos;  /* Nom réel */
//     char   *pw_dir;    /* Répertoire personnel */
//     char   *pw_shell;  /* Interpréteur de commande */
// };

// struct group *getgrgid(gid_t gid);
// struct group {
//     char   *gr_name;    /* Nom du groupe.          */
//     char   *gr_passwd;  /* Mot de passe du groupe. */
//     gid_t   gr_gid;     /* ID du groupe.           */
//     char  **gr_mem;     /* Membres du groupe.      */
// };

typedef struct		s_ls
{
	int				flag;
	char			**to_read;

	size_t			nb_elem;
	size_t			size_block;
	size_t			size_link;
	size_t			size_user;
	size_t			size_grp;
	size_t			size_size;
	size_t			total_block;

	char			*current_path;
	t_lf			**file;
}					t_ls;

int		ft_read_dir(t_ls *ls, char *path, int size);

void	ft_get_flag(t_ls *ls, int argc, char **argv);

void	ft_exit(int mode, char c);

void	ft_affich(t_ls *ls);

int		ft_ascii_cmp(t_lf *f1, t_lf *f2);

int		ft_less_s_maj_cmp(t_lf *f1, t_lf *f2);

int		ft_less_t_cmp(t_lf *f1, t_lf *f2);

char	*ft_create_path(char *path, char *file);

void	ft_recursif(t_ls *ls);

int		ft_long_format(t_ls *ls);

#endif


/*
The Long Format
     If the -l option is given, the following information is displayed for each file: file mode, number of links, owner
     name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file
     last modified, minute file last modified, and the pathname.  In addition, for each directory whose contents are dis-
     played, the total number of 512-byte blocks used by the files in the directory is displayed on a line by itself,
     immediately before the information for the files in the directory.  If the file or directory has extended
     attributes, the permissions field printed by the -l option is followed by a '@' character.  Otherwise, if the file
     or directory has extended security information (such as an access control list), the permissions field printed by
     the -l option is followed by a '+' character.

     If the modification time of the file is more than 6 months in the past or future, then the year of the last modifi-
     cation is displayed in place of the hour and minute fields.

     If the owner or group names are not a known user or group name, or the -n option is given, the numeric ID's are dis-
     played.

     If the file is a character special or block special file, the major and minor device numbers for the file are dis-
     played in the size field.  If the file is a symbolic link, the pathname of the linked-to file is preceded by ``->''.

     The file mode printed under the -l option consists of the entry type, owner permissions, and group permissions.  The
     entry type character describes the type of file, as follows:

           b     Block special file.
           c     Character special file.
           d     Directory.
           l     Symbolic link.
           s     Socket link.
           p     FIFO.
           -     Regular file.

     The next three fields are three characters each: owner permissions, group permissions, and other permissions.  Each
     field has three character positions:

           1.   If r, the file is readable; if -, it is not readable.

           2.   If w, the file is writable; if -, it is not writable.

           3.   The first of the following that applies:

                      S     If in the owner permissions, the file is not executable and set-user-ID mode is set.  If in
                            the group permissions, the file is not executable and set-group-ID mode is set.

                      s     If in the owner permissions, the file is executable and set-user-ID mode is set.  If in the
                            group permissions, the file is executable and setgroup-ID mode is set.

                      x     The file is executable or the directory is searchable.

                      -     The file is neither readable, writable, executable, nor set-user-ID nor set-group-ID mode,
                            nor sticky.  (See below.)

                These next two apply only to the third character in the last group (other permissions).

                      T     The sticky bit is set (mode 1000), but not execute or search permission.  (See chmod(1) or
                            sticky(8).)

                      t     The sticky bit is set (mode 1000), and is searchable or executable.  (See chmod(1) or
                            sticky(8).)

*/
