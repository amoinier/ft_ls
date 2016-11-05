/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/05 18:29:14 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_all_dir(char *path) {
	int		i;
	char	**list;
	char	*fpath;
	char	*newpath;

	i = 0;
	if (path)
	{
		list = ft_list_dir(path);
		if (list) {
			while (list[i])
			{
				ft_putstr(list[i]);
				ft_putchar(' ');
				i++;
			}
			i = 0;
			while (list[i])
			{
				fpath = ft_strjoin(path, "/");
				newpath = ft_strjoin(fpath, list[i]);
				ft_list_all_dir(newpath);
				ft_strdel(&fpath);
				ft_strdel(&newpath);
				i++;
			}
			ft_freedtab2(list, i);
			ft_putchar('\n');
		}
	}
	return ;
}

int	main(int ac, char **av) {
	ac = 1;
	char	*path;

	if (!av[1])
		path = ".";
	else
		path = av[1];
	ft_list_all_dir(path);
	return (0);
}
