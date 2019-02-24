/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:05:14 by slindgre          #+#    #+#             */
/*   Updated: 2019/02/24 00:39:49 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_position(tetr_list *list, uint16_t *map, int n, short x)
{
	int	i;
	short y;

	y = list->y;
	while (y + list->height <= n)
	{
		while (x + list->width <= n)
		{
			i = 0;
			while (i < 4 && !(((list->tetr << (i * 4) & 61440 ) >> x )
			& map[y + i]))
				i++;
			if (i == 4)
			{
				list->x = x;
				list->y = y;
				while (i--)
					map[y + 3 - i] |=
						((list->tetr << ((3 - i) * 4)) & 61440) >> x;
				return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

int		clear_position(tetr_list **begin_list,
		tetr_list **list, uint16_t *map, int n)
{
	tetr_list	*temp;
	int			i;

	temp = *begin_list;
	if (*list != *begin_list)
	{
		while (temp->next != *list)
			temp = temp->next;
		(*list)->x = 0;
		(*list)->y = 0;
		(*list) = temp;
		i = -1;
		while (++i < 4)
			map[(*list)->y + i] ^=
				(((*list)->tetr << (i * 4)) & 61440) >> (*list)->x;
		(*list)->x += 1;
	}
	else
	{
		ft_clean_list(begin_list);
		ft_clean_arr(map, 16);
		print_map(begin_list, list, n);
		*list = *begin_list;
		n++;
	}
	return (n + 1);
}

int		solve_map(tetr_list **begin_list, int size)
{
	uint16_t	*map;
	tetr_list	*list;
	int			i;
	int			n;

	i = 0;
	map = (uint16_t*)malloc(sizeof(uint16_t) * 16);
	while (i < 16)
		map[i++] = 0;
	n = ft_sqrt(size * 4);
	list = *begin_list;
	while (list)
		if (!check_position(list, map, n, list->x))
			n = clear_position(begin_list, &list, map, n);
		else
			list = list->next;
	return (n);
}
