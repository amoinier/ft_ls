/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:36:00 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/10 15:01:04 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	space_nbr(int val, int max)
{
	int	i;

	i = 0;
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

static	void	write_info(char *flag, t_file *list)
{
	if (ft_strchr(flag, 'l'))
	{
		ft_putstr(list->right);
		space_nbr(list->nblk, 5);
		ft_putnbr(list->nblk);
		ft_putchar(' ');
		ft_putstr(list->prop);
		ft_putstr("  ");
		ft_putstr(list->groupe);
		space_nbr(list->size, 7);
		ft_putnbr(list->size);
		ft_putchar(' ');
		ft_putnbr(list->date);
		ft_putchar(' ');
		ft_putstr(list->name);
		ft_putchar('\n');
	}
	else {
		ft_putstr(list->name);
		ft_putchar('\n');
	}
}

void			write_filename(char *flag, char *path, char *start, t_file *list)
{
	unsigned int	i;
	t_nbr			**nbr;

	i = 0;
	nbr = count_total();
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
	while (list->next)
	{
		write_info(flag, list);
		list = list->next;
		i++;
	}
	return ;
}
