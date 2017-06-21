/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:55:45 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/21 12:56:15 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>

typedef struct		s_file
{
	char			*type;
	char			*name;
	char			*realname;
	char			*right;
	int				nblk;
	char			*prop;
	char			*groupe;
	unsigned int	nb_block;
	unsigned int	size;
	time_t			date;
	int				major;
	int				minor;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct		s_nbr
{
	unsigned int	total;
	unsigned int	file;
	int				multiav;
	int				nb_for_sp;
	int				sz_for_sp;
	int				nm_for_sp;
	int				dy_for_sp;
}					t_nbr;

t_file				*ft_list_dir(char *flag, char *filename);
void				ft_list_all_dir(char *flag, char *path, char *start);

void				write_f(char *flag, char *path, char *start, t_file *list);

t_file				*ft_sort_file(char *flag, t_file *start, t_file *new);
t_file				*ft_sort(t_file *tmp, t_file *start, t_file *new);

char				ft_let_type(mode_t st_mode);
t_file				*ft_info_dir(t_file *list, char *filename);
t_file				*ft_info_file(t_file *list, char *filename);

void				ft_freedtab2(char **tab, int size);
void				free_list(t_file *list);
t_file				*free_elemt_list(t_file *list);
void				set_to_zero();

t_nbr				**count_total();
t_file				*ft_create_struct(void);

int					nb_for_space(int val);
void				space_nbr(int val, int max);
char				*to_lower(char *str);

char				*check_flag(int ac, char **av);
char				**check_type(int ac, char **av, int nbr_file, char *flag);

#endif
