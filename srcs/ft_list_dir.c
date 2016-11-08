/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:11:11 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/08 17:45:39 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	t_file		*ft_create_struct() {
	t_file	*list;

	if (!(list = (t_file *)malloc(sizeof(*list))))
		return (NULL);
	list->prev = NULL;
	list->name = NULL;
	list->next = NULL;
	return (list);
}

t_file	*ft_get_file(char *flag, struct dirent *dir, t_file *list, char *filename)
{
	t_file	*tmp;

	if (!ft_strchr(flag, 'a') && dir->d_name[0] != '.')
	{
		tmp = ft_create_struct();
		tmp->name = ft_strdup(dir->d_name);
		if (ft_strchr(flag, 'l') || ft_strchr(flag, 't'))
			tmp = ft_info_file(tmp, filename);
		list = ft_sort_file(flag, list, tmp);
	}
	else if (ft_strchr(flag, 'a'))
	{
		tmp = ft_create_struct();
		tmp->name = ft_strdup(dir->d_name);
		if (ft_strchr(flag, 'l') || ft_strchr(flag, 't'))
			tmp = ft_info_file(tmp, filename);
		list = ft_sort_file(flag, list, tmp);
	}
	return (list);
}

t_file				*ft_list_dir(char *flag, char *filename)
{
	struct	dirent *dir;
	DIR		*id_dir;
	t_file	*list;

	id_dir = opendir(filename);
	if (id_dir)
	{
		list = ft_create_struct();
		while ((dir = readdir(id_dir)))
		{
			list = ft_get_file(flag, dir, list, filename);
		}
		closedir(id_dir);
		return (list);
	}
	else
		return (NULL);
}
