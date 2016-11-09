/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/08 23:44:56 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_info(char *flag, t_file *list)
{
	if (ft_strchr(flag, 'l'))
	{
		ft_putstr(list->right);
		ft_putchar(' ');
		ft_putnbr(list->nblk);
		ft_putchar(' ');
		ft_putstr(list->prop);
		ft_putchar(' ');
		ft_putstr(list->groupe);
		ft_putchar(' ');
		ft_putnbr(list->size);
		ft_putchar(' ');
		ft_putnbr(list->date);
		ft_putchar(' ');
		ft_putstr(list->name);
		ft_putchar('\n');
	}
	else {
		ft_putstr(list->name);
		ft_putchar('\n');
	}
}

void	write_filename(char *flag, char *path, char *start, t_file *list)
{
	if (path != start)
	{
		ft_putstr(path);
		ft_putchar(':');
		ft_putchar('\n');
	}
	while (list->next)
	{
		write_info(flag, list);
		list = list->next;
	}
	ft_putchar('\n');
	return ;
}

void	ft_list_all_dir(char *flag, char *path, char *start)
{
	t_file	*list;
	t_file	*tmp;
	char	*fpath;
	char	*newpath;

	if (path)
	{
		list = ft_list_dir(flag, path);
		if (list)
		{
			tmp = list;
			write_filename(flag, path, start, tmp);
			if (ft_strchr(flag, 'R'))
			{
				while (tmp->next)
				{
					if (ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
					{
						fpath = ft_strjoin(path, "/");
						newpath = ft_strjoin(fpath, tmp->name);
						ft_list_all_dir(flag, newpath, start);
						ft_strdel(&fpath);
						ft_strdel(&newpath);
					}
					tmp = tmp->next;
				}
			}
		}
	}
	return ;
}

char		*check_flag(int ac, char **av)
{
	int	i;
	int	j;
	int	k;
	char	*flag;

	flag = ft_strnew(6);
	i = 1;
	k = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][0] == '-')
			{
				if (av[i][j] == 'R' || av[i][j] == 'l' || av[i][j] == 'a' ||
				av[i][j] == 'r' || av[i][j] == 't')
				{
					flag[k] = av[i][j];
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return (flag);
}

int	main(int ac, char **av)
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
