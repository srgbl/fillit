/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:05:14 by slindgre          #+#    #+#             */
/*   Updated: 2019/02/27 21:11:13 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_position(t_tetr *list, int i, int x)
{
	int	res;

	res = (list->tetr << (i * 4) & 61440) >> x;
	return (res);
}

int		paste_tetr(t_tetr *list, int i, int x)
{
	int	res;

	res = ((list->tetr << ((3 - i) * 4)) & 61440) >> x;
	return (res);
}

int		find_position(t_tetr *list, uint16_t *map, int n, int x)
{
	int	i;
	int	y;

	y = list->y;
	while (y + list->height <= n)
	{
		while (x + list->width <= n)
		{
			i = 0;
			while (i < 4 && !(check_position(list, i, x) & map[y + i]))
				i++;
			if (i == 4)
			{
				list->x = x;
				list->y = y;
				while (i--)
					map[y + 3 - i] |= paste_tetr(list, i, x);
				return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

int		clear_position(t_tetr **begin_list,
					t_tetr **list, uint16_t *map, int n)
{
	t_tetr	*temp;
	int		i;

	while (*list != *begin_list)
	{
		temp = *begin_list;
		while (temp->next != *list)
			temp = temp->next;
		(*list)->x = 0;
		(*list)->y = 0;
		i = -1;
		while (++i < 4)
			map[temp->y + i] ^= ((temp->tetr << (i * 4)) & 61440) >> temp->x;
		temp->x += 1;
		(*list) = temp;
		if (temp->tetr != (temp->next)->tetr)
			return (n);
	}
	ft_clean_list(begin_list);
	ft_clean_arr(map, 16);
	*list = *begin_list;
	n++;
	return (n);
}

int		solve_map(char *str)
{
	uint16_t	*map;
	t_tetr		*list;
	t_tetr		*curr;
	int			n;

	map = malloc(sizeof(uint16_t) * 16);
	ft_memset(map, 0, sizeof(uint16_t) * 16);
	n = ft_sqrt(str_to_bytes(str, &list) * 4);
	curr = list;
	while (curr)
	{
		if (!find_position(curr, map, n, curr->x))
			n = clear_position(&list, &curr, map, n);
		else
			curr = curr->next;
	}
	print_map(&list, NULL, n);
	free_list(list);
	free(map);
	return (n);
}
