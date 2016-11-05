/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:55:45 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/05 18:37:10 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>

typedef struct	s_file
{
	char			*name;
	char			*right;
	int				nblk;
	char			*prop;
	char			*groupe;
	int				size;
	char			*date;
	struct s_file	*next;
}				t_file;

char	**ft_list_dir(char *filename);
void	ft_info_file(char *filename);
void	ft_freedtab2(char **tab, int size);
char	**sort_name(char **list);

#endif
