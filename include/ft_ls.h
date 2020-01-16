/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:22:40 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/16 18:19:09 by floblanc         ###   ########.fr       */
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
# include "libprintf.h"

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

typedef struct	s_ls
{
	int			flag;
	char		**to_read;
}				t_ls;

#endif