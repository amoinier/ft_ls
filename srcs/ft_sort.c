/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:40:55 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/08 15:46:52 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file *ft_sort_file(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->name && ft_strcmp(tmp->name, new->name) < 0)
		tmp = tmp->next;
	new->next = tmp;
	if (tmp->prev)
		tmp->prev->next = new;
	tmp->prev = new;
	while (start->prev)
		start = start->prev;
	return (start);
}
