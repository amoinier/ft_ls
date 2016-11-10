/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:37:40 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/10 21:26:39 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_freedtab2(char **tab, int size)
{
	int	i;

	i = size;
	if (tab == NULL)
	{
		free(tab);
		tab = NULL;
		return ;
	}
	while (i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
}

t_nbr	**count_total()
{
	static t_nbr *nbr;

	if (!nbr)
	{
		if (!(nbr = (t_nbr *)malloc(sizeof(*nbr))))
			return (NULL);
		nbr->total = 0;
		nbr->file = 0;
		nbr->nb_for_sp = 0;
		nbr->sz_for_sp = 0;
	}
	return (&nbr);
}

char	*to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}
