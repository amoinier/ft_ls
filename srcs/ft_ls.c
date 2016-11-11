/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/11 13:33:30 by amoinier         ###   ########.fr       */
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
	t_file	*list;
	t_file	*tmp;

	if (path)
	{
		list = ft_list_dir(flag, path);
		if (list)
		{
			tmp = list;
			write_f(flag, path, start, tmp);
			if (ft_strchr(flag, 'R'))
			{
				while (tmp->next)
				{
					if (ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
						flag_gr(flag, path, start, tmp);
					tmp = tmp->next;
				}
			}
		}
	}
}

static	void	error_flag(char fl)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(fl);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
	exit(0);
}

char			*check_flag(int ac, char **av)
{
	int		i;
	int		j;
	int		k;
	char	*flag;

	flag = ft_strnew(6);
	i = 1;
	k = 0;
	while (i < ac)
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][0] == '-')
			{
				if (av[i][j] == 'R' || av[i][j] == 'l' || av[i][j] == 'a' ||
				av[i][j] == 'r' || av[i][j] == 't')
					flag[k++] = av[i][j];
				else if (av[i][j] != ' ' && av[i][j] != '-')
					error_flag(av[i][j]);
			}
			j++;
		}
		i++;
	}
	return (flag);
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
