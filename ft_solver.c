/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:05:14 by slindgre          #+#    #+#             */
/*   Updated: 2019/02/27 03:33:16 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void print_map(tetr_list **list, tetr_list *curr, int n)
{
	tetr_list	*temp;
	char		str[17][17];
	int			i;
	int			k;

	i = 0;
	while (i < n)
	{
		ft_memset(str[i], '\0', 16);
		ft_memset(str[i], '.', (size_t)n);
		str[i++][n] = '\0';
	}
	k = 0;
	temp = *list;
	while (temp != curr)
	{
		i = -1;
		while (++i < 16)
			if (temp->tetr & (1 << (15 - i)))
				str[temp->y + i / 4][temp->x + i % 4] = 'A' + k;
		k++;
		temp = temp->next;
	}
	i = 0;
	while (i < n)
		ft_putendl(str[i++]);
}

int	check_position(tetr_list *list, uint16_t *map, int n, int x)
{
	int	i;
	int y;

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

int	clear_position(tetr_list **begin_list,
		tetr_list **list, uint16_t *map, int n)
{
	tetr_list	*temp;
	int			i;

	while (*list != *begin_list)
	{
		temp = *begin_list;
		while (temp->next != *list)
			temp = temp->next;
		(*list)->x = 0;
		(*list)->y = 0;
		i = -1;
		while (++i < 4)
			map[temp->y + i] ^=
				((temp->tetr << (i * 4)) & 61440) >> temp->x;
		temp->x += 1;
		(*list) = temp;
		if (temp->tetr != (temp->next)->tetr)
			return(n);
	}
		ft_clean_list(begin_list);
		ft_clean_arr(map, 16);
		*list = *begin_list;
		n++;
	return(n);
}

int	solve_map(char *str)
{
	uint16_t	*map;
	tetr_list	*list;
	tetr_list	*curr;
	int			n;

	map = malloc(sizeof(uint16_t) * 16);
	ft_memset(map, 0, sizeof(uint16_t) * 16);
	n = ft_sqrt(str_to_bytes(str, &list) * 4);
	curr = list;
	while (curr)
	{

		if (!check_position(curr, map, n, curr->x))
			n = clear_position(&list, &curr, map, n);
		else
		{
/*			if (curr == list)
			{
			ft_putstr("\nn = ");
			ft_putnbr(n);
			ft_putstr("\n");
			print_map(&list, curr->next, n);
			}
*/			curr = curr->next;
		}
	}
	print_map(&list, NULL, n);
	free_list(list);
	free(map);
	return (n);
}
