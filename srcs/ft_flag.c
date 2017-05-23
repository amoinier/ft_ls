/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:18:36 by amoinier          #+#    #+#             */
/*   Updated: 2017/05/23 15:57:26 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	error_flag(char fl)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(fl);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
	exit(1);
}

static	char	*do_flag(char *flag, char c, int *k)
{
	if (c == 'R' || c == 'l' || c == 'a' ||
	c == 'r' || c == 't')
		flag[k[0]++] = c;
	else if (c != ' ')
		error_flag(c);
	return (flag);
}

char			*check_flag(int ac, char **av)
{
	int		i;
	int		j;
	int		k;
	char	*flag;

	if (!(flag = ft_strnew(6)))
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
