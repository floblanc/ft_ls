/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:22:40 by floblanc          #+#    #+#             */
/*   Updated: 2020/01/16 14:12:01 by apouchet         ###   ########.fr       */
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

# define A 1
# define L 2

typedef struct	s_ls
{
	int			flag;
	char		**to_read;
}				t_ls;

#endif