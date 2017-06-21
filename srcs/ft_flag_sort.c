/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:18:36 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/21 13:33:07 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**alphabetic_sort(char **av, int j, int k)
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
	return (av);
}

static char		**time_sort(char **av, int j, int k, char **file)
{
	char			*tmp;
	int				tmpint;
	struct stat		info;
	struct stat		info2;

	while (av[j] && av[j][0])
	{
		k = j + 1;
		tmp = NULL;
		lstat(av[j], &info);
		while (av[k] && av[k][0])
		{
			lstat(av[k], &info2);
			if ((int)(info.st_mtime - info2.st_mtime) < 0 && (tmpint = k))
				tmp = ft_strdup(av[k]);
			k++;
		}
		if (tmp)
			av[tmpint] = ft_strdup(av[j]);
		if (tmp)
			av[j] = tmp;
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

char			**check_type(int ac, char **av, int nbr_file, char *flag)
{
	int				j;
	int				k;
	char			**file;

	j = nbr_file;
	k = 0;
	if (!(file = (char **)malloc(sizeof(char *) * (ac - nbr_file + 1))))
		return (NULL);
	av = alphabetic_sort(av, j, k);
	if (ft_strchr(flag, 't'))
		file = time_sort(av, j, k, file);
	file = type_sort(av, nbr_file, k, file);
	return (file);
}
