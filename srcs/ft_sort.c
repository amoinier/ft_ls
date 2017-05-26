/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:40:55 by amoinier          #+#    #+#             */
/*   Updated: 2017/05/26 11:48:59 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	t_file	*ft_sort(t_file *tmp, t_file *start, t_file *new)
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

t_file		*ft_normal_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->name && ft_strcmp(tmp->name, new->name) < 0)
		tmp = tmp->next;
	return (ft_sort(tmp, start, new));
}

t_file		*ft_inverte_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->name && ft_strcmp(tmp->name, new->name) >= 0)
		tmp = tmp->next;
	return (ft_sort(tmp, start, new));
}

t_file		*ft_normal_t_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->name && (int)(tmp->date - new->date) >= 0) {
		if ((int)(tmp->date - new->date) == 0) {
			if (ft_strcmp(to_lower(tmp->name), to_lower(new->name)) >= 0) {
				break ;
			}
		}
		tmp = tmp->next;
	}
	return (ft_sort(tmp, start, new));
}

t_file		*ft_inverte_t_sort(t_file *start, t_file *new)
{
	t_file	*tmp;

	tmp = start;
	while (tmp && tmp->name && (int)(tmp->date - new->date) < 0)
		tmp = tmp->next;
	return (ft_sort(tmp, start, new));
}

t_file		*ft_sort_file(char *flag, t_file *start, t_file *new)
{
	if (ft_strchr(flag, 'r'))
	{
		if (ft_strchr(flag, 't'))
			return (ft_inverte_t_sort(start, new));
		else
			return (ft_inverte_sort(start, new));
	}
	else
	{
		if (ft_strchr(flag, 't'))
			return (ft_normal_t_sort(start, new));
		else
			return (ft_normal_sort(start, new));
	}
}
