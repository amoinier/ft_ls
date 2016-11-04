/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:11:11 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/04 13:44:49 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_list_dir(char *filename)
{
	struct dirent *dir;
	DIR *id_dir;

	id_dir = opendir(filename);
	while ((dir = readdir(id_dir))) {
		ft_putstr(dir->d_name);
		ft_putchar('\n');
	}
	closedir(id_dir);
	return ;
}
