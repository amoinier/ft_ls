/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:37:40 by amoinier          #+#    #+#             */
/*   Updated: 2017/05/23 15:48:35 by amoinier         ###   ########.fr       */
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

t_nbr	**count_total(void)
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
		nbr->nm_for_sp = 0;
		nbr->multiav = 0;
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


t_file	*ft_create_struct(void)
{
	t_file	*list;

	if (!(list = (t_file *)malloc(sizeof(*list))))
		return (NULL);
	list->prev = NULL;
	list->name = NULL;
	list->realname = NULL;
	list->right = NULL;
	list->prop = NULL;
	list->groupe = NULL;
	list->date = 0;
	list->major = -1;
	list->minor = -1;
	list->next = NULL;
	return (list);
}

int		nb_for_space(int val)
{
	int	i;

	i = 0;
	while (val != 0)
	{
		val = val / 10;
		i++;
	}
	return (i + 2);
}

t_file	*free_elemt_list(t_file *list)
{
	if (list && list->name)
	ft_strdel(&list->name);
	if (list && list->right)
	ft_strdel(&list->right);
	if (list && list->realname)
	ft_strdel(&list->realname);
	free(list);
	list = NULL;
	return (list);
}
