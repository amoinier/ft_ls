/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:40:55 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/08 17:35:18 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file *ft_normal_sort(t_file *start, t_file *new)
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

t_file *ft_inverte_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->name && ft_strcmp(tmp->name, new->name) >= 0)
		tmp = tmp->next;
	new->next = tmp;
	if (tmp->prev)
		tmp->prev->next = new;
	tmp->prev = new;
	while (start->prev)
		start = start->prev;
	return (start);
}

t_file *ft_normal_t_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->date && tmp->date < new->date)
		tmp = tmp->next;
	new->next = tmp;
	if (tmp->prev)
		tmp->prev->next = new;
	tmp->prev = new;
	while (start->prev)
		start = start->prev;
	return (start);
}

t_file *ft_inverte_t_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->date && tmp->date > new->date)
		tmp = tmp->next;
	new->next = tmp;
	if (tmp->prev)
		tmp->prev->next = new;
	tmp->prev = new;
	while (start->prev)
		start = start->prev;
	return (start);
}

t_file *ft_sort_file(char *flag, t_file *start, t_file *new)
{
	if (ft_strchr(flag, 'r'))
	{
		if (ft_strchr(flag, 't'))
			return(ft_inverte_t_sort(start, new));
		else
			return(ft_inverte_sort(start, new));
	}
	else
	{
		if (ft_strchr(flag, 't'))
			return(ft_normal_t_sort(start, new));
		else
			return(ft_normal_sort(start, new));
	}
}
