/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:52:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/08 16:08:33 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls(int ac, char **av, char *flag, int i)
{
	t_nbr	**nbr;

	nbr = count_total();
	if (av[i + 1])
		nbr[0]->multiav = 1;
	av = check_type(ac, av, i);
	i = 0;
	while (av[i] && av[i][0])
	{
		ft_list_all_dir(flag, av[i], av[i]);
		ft_strdel(&av[i]);
		nbr[0]->multiav++;
		i++;
	}
	free(av);
	av = NULL;
}

int				main(int ac, char **av)
{
	char	*flag;
	int		i;

	i = 1;
	flag = check_flag(ac, av);
	while (av[i] && av[i][0] == '-' && (av[i][1] &&
		ft_strchr("Ralrt1-", av[i][1])))
	{
		i++;
	}
	if (ac <= 1 || (av[ac - 1][0] == '-' && (av[ac - 1][1] &&
		ft_strchr("Ralrt1-", av[ac - 1][1]))))
	{
		ft_list_all_dir(flag, ".", ".");
	}
	else
	{
		ft_ls(ac, av, flag, i);
	}
	ft_strdel(&flag);
	return (1);
}
