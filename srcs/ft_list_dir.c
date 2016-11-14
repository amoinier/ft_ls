/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:11:11 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/14 16:14:25 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*ft_cg(char *flag, struct dirent *dir, t_file *list, char *file)
{
	t_file	*tmp;
	t_nbr	**nbr;

	nbr = count_total();
	tmp = ft_create_struct();
	tmp->name = ft_strdup(dir->d_name);
	if (ft_strchr(flag, 'l') || ft_strchr(flag, 't'))
	{
		tmp = ft_info_dir(tmp, file);
		nbr[0]->total += tmp->nb_block;
		if (nb_for_space(tmp->nb_block) >= nbr[0]->nb_for_sp)
			nbr[0]->nb_for_sp = nb_for_space(tmp->nb_block);
		if (nb_for_space(tmp->size) >= nbr[0]->sz_for_sp)
			nbr[0]->sz_for_sp = nb_for_space(tmp->size);
		if ((int)ft_strlen(tmp->prop) >= nbr[0]->nm_for_sp)
			nbr[0]->nm_for_sp = ft_strlen(tmp->prop);
	}
	nbr[0]->file += 1;
	list = ft_sort_file(flag, list, tmp);
	return (list);
}

t_file			*ft_g(char *flag, struct dirent *dir, t_file *list, char *file)
{
	if (!ft_strchr(flag, 'a') && dir->d_name[0] != '.')
		list = ft_cg(flag, dir, list, file);
	else if (ft_strchr(flag, 'a'))
		list = ft_cg(flag, dir, list, file);
	return (list);
}

t_file			*ft_list_dir(char *flag, char *filename)
{
	struct dirent	*dir;
	DIR				*id_dir;
	t_file			*list;
	t_nbr			**nbr;

	id_dir = opendir(filename);
	nbr = count_total();
	nbr[0]->total = 0;
	if (id_dir)
	{
		list = ft_create_struct();
		while ((dir = readdir(id_dir)))
		{
			list = ft_g(flag, dir, list, filename);
		}
		closedir(id_dir);
		return (list);
	}
	else
		return (NULL);
}
