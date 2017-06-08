/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:37:40 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/08 16:25:04 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_freedtab2(char **tab, int size)
{
	int			i;

	i = size;
	if (tab == NULL)
	{
		ft_strdel(tab);
		tab = NULL;
		return ;
	}
	while (i >= 0)
	{
		ft_strdel(&tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
}

t_file				*free_elemt_list(t_file *list)
{
	if (list)
	{
		if (list->name)
			ft_strdel(&list->name);
		if (list->realname)
			ft_strdel(&list->realname);
		if (list->right)
			ft_strdel(&list->right);
		if (list->realname)
			ft_strdel(&list->realname);
		if (list->type)
			ft_strdel(&list->type);
		if (list->prop)
			ft_strdel(&list->prop);
		if (list->groupe)
			ft_strdel(&list->groupe);
	}
	free(list);
	list = NULL;
	return (list);
}

void				free_list(t_file *list)
{
	t_file		*tmp;

	tmp = list;
	while (tmp->next)
	{
		if (tmp->prev)
			tmp->prev = free_elemt_list(tmp->prev);
		tmp = tmp->next;
	}
	if (tmp->prev)
		tmp->prev = free_elemt_list(tmp->prev);
	if (tmp->next)
		tmp->next = free_elemt_list(tmp->next);
	if (tmp)
		tmp = free_elemt_list(tmp);
}

void				set_to_zero(void)
{
	t_nbr		**nbr;

	nbr = count_total();
	nbr[0]->total = 0;
	nbr[0]->nb_for_sp = 0;
	nbr[0]->sz_for_sp = 0;
	nbr[0]->nm_for_sp = 0;
	nbr[0]->dy_for_sp = 0;
	return ;
}
