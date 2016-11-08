/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:55:45 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/08 17:40:58 by amoinier         ###   ########.fr       */
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
	unsigned int	size;
	unsigned int	date;
	struct s_file	*next;
	struct s_file	*prev;
}				t_file;

t_file	*ft_list_dir(char *flag, char *filename);
t_file	*ft_info_file(t_file *list, char *filename);
void	ft_freedtab2(char **tab, int size);
t_file 	*ft_sort_file(char *flag, t_file *start, t_file *new);

#endif
