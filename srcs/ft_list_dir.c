/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:11:11 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/05 18:39:20 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**ft_list_dir(char *filename)
{
	struct	dirent *dir;
	DIR		*id_dir;
	t_file	*list;
	int		i;

	id_dir = opendir(filename);
	if (id_dir) {
		i = 0;
		if (!(list = (t_list *)malloc(sizeof(list))))
			return (NULL);
		while ((dir = readdir(id_dir)))
		{
			if (dir->d_name[0] != '.')
			{
				list = ft_realloc_dstr(list, dir->d_name, i);
				i++;
			}
		}
		ft_putchar('\n');
		list[i] = NULL;
		closedir(id_dir);
		sort_name(list);
		return (list);
	}
	return (NULL);
}
