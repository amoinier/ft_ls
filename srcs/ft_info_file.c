/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:30:44 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/03 22:12:23 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_info_file(char *filename)
{
	struct	stat	info;
	char *test;

	test = ft_strjoin("./", filename);
	ft_putstr(test);
	stat(test, &info);
	return ;
}
