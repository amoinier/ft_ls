/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:18:36 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/08 17:04:35 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	char	*do_flag(char *flag, char c, int *k)
{
	if (ft_strchr("Ralrt1-", c))
		flag[k[0]++] = c;
	else if (c != ' ')
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(c);
		ft_putstr("\nusage: ls [-Ralrt1] [file ...]\n");
		exit(1);
	}
	return (flag);
}

char			*check_flag(int ac, char **av)
{
	int			i;
	int			j;
	int			k;
	char		*flag;

	if (!(flag = ft_strnew(8)))
		return (NULL);
	i = 1;
	k = 0;
	while (i < ac)
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][0] == '-')
				flag = do_flag(flag, av[i][j], &k);
			j++;
		}
		i++;
	}
	return (flag);
}

static char		**alphabetic_sort(char **av, int j, int k, char **file)
{
	char			*tmp;
	int				tmpint;

	while (av[j] && av[j][0])
	{
		k = j + 1;
		tmp = NULL;
		while (av[k] && av[k][0])
		{
			if (ft_strcmp(av[j], av[k]) > 0)
			{
				tmp = ft_strdup(av[k]);
				tmpint = k;
			}
			k++;
		}
		if (tmp)
		{
			av[tmpint] = ft_strdup(av[j]);
			av[j] = tmp;
		}
		j++;
	}
	return (file);
}

static char		**type_sort(char **av, int nbr_file, int k, char **file)
{
	struct stat		info;
	int				j;

	j = nbr_file;
	while (av[j] && av[j][0])
	{
		lstat(av[j], &info);
		if (!S_ISDIR(info.st_mode))
			file[k] = ft_strdup(av[j]);
		if (!S_ISDIR(info.st_mode))
			k++;
		j++;
	}
	j = nbr_file;
	while (av[j] && av[j][0])
	{
		lstat(av[j], &info);
		if (S_ISDIR(info.st_mode))
			file[k] = ft_strdup(av[j]);
		if (S_ISDIR(info.st_mode))
			k++;
		j++;
	}
	file[k] = "\0";
	return (file);
}

char			**check_type(int ac, char **av, int nbr_file)
{
	int				j;
	int				k;
	char			**file;

	j = nbr_file;
	k = 0;
	if (!(file = (char **)malloc(sizeof(char *) * (ac - nbr_file + 1))))
		return (NULL);
	file = alphabetic_sort(av, j, k, file);
	file = type_sort(av, nbr_file, k, file);
	return (file);
}
