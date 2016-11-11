/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:36:00 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/11 18:43:57 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	space_nbr(int val, int max)
{
	int	i;

	i = 0;
	if (val == 0)
		i++;
	while (val != 0)
	{
		val = val / 10;
		i++;
	}
	while (max - i > 0)
	{
		ft_putchar(' ');
		i++;
	}
}

static	void	first_part_write(t_file *list, t_nbr **nbr)
{
	ft_putstr(list->right);
	space_nbr(list->nblk, nbr[0]->nb_for_sp);
	ft_putnbr(list->nblk);
	ft_putchar(' ');
	ft_putstr(list->prop);
	space_nbr(ft_power(10, ft_strlen(list->prop)), nbr[0]->nm_for_sp + 3);
	ft_putstr(list->groupe);
	space_nbr(list->size, nbr[0]->sz_for_sp);
	ft_putnbr(list->size);
	ft_putchar(' ');
	ft_putstr(ft_strsub(ctime(&list->date), 4,
	ft_strlen(ctime(&list->date)) - 13));
	ft_putchar(' ');
	ft_putstr(list->name);
}

static	void	write_info(char *flag, t_file *list)
{
	t_nbr		**nbr;

	nbr = count_total();
	if (ft_strchr(flag, 'l'))
	{
		first_part_write(list, nbr);
		if (list->right[0] == 'l' && list->realname)
		{
			ft_putstr(" -> ");
			ft_putstr(list->realname);
		}
		ft_putchar('\n');
	}
	else
	{
		ft_putstr(list->name);
		ft_putchar('\n');
	}
}

void			write_f(char *flag, char *path, char *start, t_file *list)
{
	t_nbr			**nbr;

	nbr = count_total();
	if (list && list->right && (!list->right[1] || list->right[1] != 'r'))
	{
		ft_putstr("\n");
		ft_putstr(path);
		ft_putstr(":\n");
		ft_putstr("ls: ");
		ft_putstr(path);
		ft_putstr(": Permission denied\n");
		return ;
	}
	if (path != start)
	{
		ft_putstr(path);
		ft_putchar(':');
		ft_putchar('\n');
	}
	if (ft_strchr(flag, 'l'))
	{
		ft_putstr("total ");
		ft_putnbr(nbr[0]->total);
		ft_putchar('\n');
	}
	while (list && list->name)
	{
		write_info(flag, list);
		list = list->next;
	}
	return ;
}
