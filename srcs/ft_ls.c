/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/05/26 18:29:13 by amoinier         ###   ########.fr       */
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
	char		**date;

	if (path)
	{
		tmp = ft_list_dir(flag, path);

		lstat(path, &info);
		nbr = count_total();
		if ((S_ISLNK(info.st_mode) && ft_strchr(flag, 'l')) || !tmp)
		{
			tmp = ft_create_struct();
			tmp->name = path;
			tmp = ft_info_file(tmp, path);

			date = ft_strsplit(ctime(&tmp->date), ' ');

			if (tmp->right[0] != 'd' && tmp->right[1] == 'r' && path == start)
			{
				if (nb_for_space(tmp->nblk) >= nbr[0]->nb_for_sp)
					nbr[0]->nb_for_sp = nb_for_space(tmp->nblk);
				if (nb_for_space(tmp->size) >= nbr[0]->sz_for_sp)
					nbr[0]->sz_for_sp = nb_for_space(tmp->size);
				if ((int)ft_strlen(tmp->prop) >= nbr[0]->nm_for_sp)
					nbr[0]->nm_for_sp = ft_strlen(tmp->prop);
				if (nb_for_space(ft_atoi(date[2])) >= nbr[0]->dy_for_sp)
					nbr[0]->dy_for_sp = nb_for_space(ft_atoi(date[2]));

				tmp->next = NULL;

				write_f(flag, path, start, tmp);
				nbr[0]->total = 0;
				nbr[0]->nb_for_sp = 0;
				nbr[0]->sz_for_sp = 0;
				nbr[0]->nm_for_sp = 0;
				nbr[0]->dy_for_sp = 0;
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

			tmp->type = ft_strdup("dir");
			write_f(flag, path, start, tmp);
			nbr[0]->total = 0;
			nbr[0]->nb_for_sp = 0;
			nbr[0]->sz_for_sp = 0;
			nbr[0]->nm_for_sp = 0;
			nbr[0]->dy_for_sp = 0;

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

char			**check_type(int ac, char **av, int nbr_file)
{
	int		j;
	int		k;
	int 	tmpint;
	char	*tmp;
	char	**file;
	struct stat	info;

	if (!(file = (char **)malloc(sizeof(char *) * (ac - nbr_file + 1))))
		return NULL;

	j = nbr_file;
	while (av[j] && av[j][0])
	{
		k = j + 1;
		tmp = NULL;
		while (av[k] && av[k][0]) {
			if (ft_strcmp(av[j], av[k]) > 0) {
				tmp = ft_strdup(av[k]);
				tmpint = k;
			}
			k++;
		}
		if (tmp) {
			av[tmpint] = ft_strdup(av[j]);
			av[j] = ft_strdup(tmp);
		}
		j++;
	}

	j = nbr_file;
	k = 0;
	while (av[j] && av[j][0])
	{
		lstat(av[j], &info);
		if (!S_ISDIR(info.st_mode)) {
			file[k] = ft_strdup(av[j]);
			k++;
		}
		j++;
	}

	j = nbr_file;
	while (av[j] && av[j][0])
	{
		lstat(av[j], &info);
		if (S_ISDIR(info.st_mode)) {
			file[k] = ft_strdup(av[j]);
			k++;
		}
		j++;
	}
	file[k] = "\0";

	return (file);
}

int				main(int ac, char **av)
{
	char	*flag;
	t_nbr	**nbr;
	int		i;

	i = 1;
	flag = check_flag(ac, av);
	while (av[i] && av[i][0] == '-' && (av[i][1] && ft_strchr("Ralrt1-", av[i][1]))) {
		i++;
	}
	if (ac <= 1 || (av[ac - 1][0] == '-' && (av[ac - 1][1] && ft_strchr("Ralrt1-", av[ac - 1][1])))) {
		ft_list_all_dir(flag, ".", ".");
		av[i] = (av[i] ? av[i] : ".");
	}
	else
	{
		nbr = count_total();
		if (av[i + 1])
			nbr[0]->multiav = 1;
		av = check_type(ac, av, i);
		i = 0;
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
