/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:18:36 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/21 13:30:45 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	char	*do_flag(char *flag, char c, int *k)
{
	if (ft_strchr("Ralrt1-", c))
		flag[k[0]++] = c;
	else if (c != ' ')
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(c);
		ft_putstr("\nusage: ls [-Ralrt1] [file ...]\n");
		exit(1);
	}
	return (flag);
}

char			*check_flag(int ac, char **av)
{
	int			i;
	int			j;
	int			k;
	char		*flag;

	if (!(flag = ft_strnew(8)))
		return (NULL);
	i = 1;
	k = 0;
	while (i < ac)
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][0] == '-')
				flag = do_flag(flag, av[i][j], &k);
			j++;
		}
		i++;
	}
	return (flag);
}
