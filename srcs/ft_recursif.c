/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/21 11:38:28 by amoinier         ###   ########.fr       */
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
	ft_strdel(&newpath);
	if (path[ft_strlen(path) - 1] != '/')
		ft_strdel(&fpath);
}

static void		is_file_part2(char *flag, char *path, char *start, t_file *tmp)
{
	char		**date;
	t_nbr		**nbr;

	nbr = count_total();
	date = ft_strsplit(ctime(&tmp->date), ' ');
	if (nb_for_space(tmp->nblk) >= nbr[0]->nb_for_sp)
		nbr[0]->nb_for_sp = nb_for_space(tmp->nblk);
	if (nb_for_space(tmp->size) >= nbr[0]->sz_for_sp)
		nbr[0]->sz_for_sp = nb_for_space(tmp->size);
	if ((int)ft_strlen(tmp->prop) >= nbr[0]->nm_for_sp)
		nbr[0]->nm_for_sp = ft_strlen(tmp->prop);
	if (nb_for_space(ft_atoi(date[2])) >= nbr[0]->dy_for_sp)
		nbr[0]->dy_for_sp = nb_for_space(ft_atoi(date[2]));
	ft_freedtab2(date, 5);
	write_f(flag, path, start, tmp);
	set_to_zero();
}

static void		is_file(char *flag, char *path, char *start, t_file *tmp)
{
	t_nbr		**nbr;

	tmp = ft_create_struct();
	tmp->name = (!tmp->name ? ft_strdup(path) : tmp->name);
	tmp = ft_info_file(tmp, path);
	nbr = count_total();
	if (tmp->right[0] != 'd' && tmp->right[1] == 'r' && path == start)
	{
		is_file_part2(flag, path, start, tmp);
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
	free_list(tmp);
}

static void		is_directory(char *flag, char *path, char *start, t_file *tmp)
{
	t_file		*ttest;

	if (ft_strchr(flag, 'R') && path != start)
		ft_putchar('\n');
	tmp->type = (tmp->type ? tmp->type : ft_strdup("dir"));
	write_f(flag, path, start, tmp);
	set_to_zero();
	if (ft_strchr(flag, 'R'))
	{
		ttest = tmp;
		while (ttest->next)
		{
			if (ft_strcmp(ttest->name, ".") &&
			ft_strcmp(ttest->name, ".."))
				flag_gr(flag, path, start, ttest);
			ttest = ttest->next;
		}
	}
	free_list(tmp);
}

void			ft_list_all_dir(char *flag, char *path, char *start)
{
	t_file		*tmp;
	struct stat	info;

	if (path)
	{
		tmp = ft_list_dir(flag, path);
		lstat(path, &info);
		if ((S_ISLNK(info.st_mode) && ft_strchr(flag, 'l')) || !tmp)
		{
			is_file(flag, path, start, tmp);
		}
		else if (tmp)
		{
			is_directory(flag, path, start, tmp);
		}
	}
}
