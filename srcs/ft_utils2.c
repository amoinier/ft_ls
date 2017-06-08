/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:37:40 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/08 16:18:55 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			ft_let_type(mode_t st_mode)
{
	if (S_ISSOCK(st_mode))
		return ('s');
	else if (S_ISFIFO(st_mode))
		return ('f');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISREG(st_mode))
		return ('-');
	else
		return ('-');
}

t_file			*ft_sort(t_file *tmp, t_file *start, t_file *new)
{
	if (tmp && tmp->prev)
		new->prev = tmp->prev;
	new->next = tmp;
	if (tmp)
	{
		if (tmp->prev)
			tmp->prev->next = new;
		tmp->prev = new;
	}
	while (start->prev)
		start = start->prev;
	return (start);
}
