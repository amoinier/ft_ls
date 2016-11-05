/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:40:55 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/05 18:34:36 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**sort_name(char **list)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	while (list[i])
	{
		j = i + 1;
		tmp = ft_strdup(list[i]);
		while (list[j])
		{
			if (strcmp(tmp, list[j]) >= 0)
			{
				tmp = ft_strdup(list[j]);
				k = j;
			}
			j++;
		}
		if(tmp != list[i])
		{
			list[k] = ft_strdup(list[i]);
			list[i] = ft_strdup(tmp);
		}
		i++;
	}
	return (list);
}

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned	int	i;
	unsigned	int	j;
	int				k;
	int	tmp;

	i = 0;
	k = 0;
	while (i < size)
	{
		j = i + 1;
		tmp = tab[i];
		while (j < size)
		{
			if (tmp >= tab[j])
			{
				tmp = tab[j];
				k = j;
			}
			j++;
		}
		if (tmp != tab[i])
		{
			tab[k] = tab[i];
			tab[i] = tmp;
		}
		i++;
	}
}
