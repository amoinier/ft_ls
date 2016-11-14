/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/14 03:45:00 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	flag_gr(char *flag, char *path, char *start, t_file *tmp)
{
	char	*fpath;
	char	*newpath;

	fpath = ft_strjoin(path, "/");
	newpath = ft_strjoin(fpath, tmp->name);
	ft_list_all_dir(flag, newpath, start);
	ft_strdel(&fpath);
	ft_strdel(&newpath);
}

void			ft_list_all_dir(char *flag, char *path, char *start)
{
	t_file	*tmp;
	t_nbr	**nbr;

	if (path)
	{
		tmp = ft_list_dir(flag, path);
		if (tmp)
		{
			if (ft_strchr(flag, 'R') && path != start)
				ft_putchar('\n');
			write_f(flag, path, start, tmp);
			if (ft_strchr(flag, 'R'))
			{
				while (tmp->next)
				{
					if (ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
						flag_gr(flag, path, start, tmp);
					tmp = tmp->next;
					free_elemt_list(tmp->prev);
					tmp->prev = NULL;
				}
			}
		}
		else
		{
			nbr = count_total();
			tmp = ft_create_struct();
			tmp->name = path;
			tmp = ft_info_file(tmp, path);
			if (tmp->right[0] != 'd' && tmp->right[1] == 'r' && path == start)
			{
				if (nb_for_space(tmp->nb_block) >= nbr[0]->nb_for_sp)
				nbr[0]->nb_for_sp = nb_for_space(tmp->nb_block);
				if (nb_for_space(tmp->size) >= nbr[0]->sz_for_sp)
				nbr[0]->sz_for_sp = nb_for_space(tmp->size);
				if ((int)ft_strlen(tmp->prop) >= nbr[0]->nm_for_sp)
				nbr[0]->nm_for_sp = ft_strlen(tmp->prop);
				tmp->next = NULL;
				write_f(flag, path, start, tmp);
			}
			else if (tmp->right[0] == 'd')
			{
				ft_putstr("\n");
				ft_putstr(path);
				ft_putstr(":\n");
				ft_putstr("ls: ");
				ft_putstr(path);
				ft_putstr(": Permission denied\n");
			}
			else
			{
				ft_putstr("ls: ");
				ft_putstr(path);
				ft_putstr(": No such file or directory\n");
				return ;
			}
		}
	}
}

int				main(int ac, char **av)
{
	char	*path;
	char	*flag;

	flag = check_flag(ac, av);
	if (ac <= 1 || av[ac - 1][0] == '-')
		path = ".";
	else
		path = av[ac - 1];
	ft_list_all_dir(flag, path, path);
	return (0);
}
