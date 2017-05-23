/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/05/23 18:36:02 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	flag_gr(char *flag, char *path, char *start, t_file *tmp)
{
	char	*fpath;
	char	*newpath;

	if (path[ft_strlen(path) - 1] != '/')
	{
		fpath = ft_strjoin(path, "/");
		newpath = ft_strjoin(fpath, tmp->name);
	}
	else
		newpath = ft_strjoin(path, tmp->name);

	ft_list_all_dir(flag, newpath, start);

	if (path[ft_strlen(path) - 1] != '/')
	{
		ft_strdel(&fpath);
		ft_strdel(&newpath);
	}
}

void			ft_list_all_dir(char *flag, char *path, char *start)
{
	t_file		*tmp;
	t_nbr		**nbr;
	struct stat	info;

	if (path)
	{
		tmp = ft_list_dir(flag, path);

		lstat(path, &info);
		if ((S_ISLNK(info.st_mode) && ft_strchr(flag, 'l')) || !tmp)
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
				if (ft_strchr(flag, 'R'))
				{
					ft_putstr("\n");
					ft_putstr(path);
					ft_putstr(":\n");
				}
				ft_putstr("ls: ");
				ft_putstr(path);
				ft_putstr(": Permission denied\n");
			}
		}
		else if (tmp)
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
					tmp->prev = free_elemt_list(tmp->prev);
					tmp->prev = NULL;
				}
			}
			else {
				tmp->next = free_elemt_list(tmp->next);
				tmp = free_elemt_list(tmp);
				tmp = NULL;
			}
		}
	}
}

int				main(int ac, char **av)
{
	char	*flag;
	t_nbr	**nbr;
	int		i;

	i = 1;
	flag = check_flag(ac, av);
	while (av[i] && av[i][0] == '-') {
		i++;
	}
	if (ac <= 1 || av[ac - 1][0] == '-') {
		ft_list_all_dir(flag, ".", ".");
		av[i] = (av[i] ? av[i] : ".");
	}
	else
	{
		nbr = count_total();
		if (av[i + 1])
			nbr[0]->multiav = 1;
		while (av[i] && av[i][0])
		{
			ft_list_all_dir(flag, av[i], av[i]);
			nbr[0]->multiav++;
			i++;
		}
		ft_strdel(&flag);
	}
	return (0);
}
