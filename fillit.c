/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:05:14 by slindgre          #+#    #+#             */
/*   Updated: 2019/02/23 20:28:58 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/includes/libft.h"

typedef struct		m_list
{
	uint16_t		tetr;
	short			width;
	short			height;
	short			x;
	short			y;
	struct m_list	*next;
}					tetr_list;

tetr_list	*ft_create_elem(void)
{
	tetr_list	*new_elem;

	new_elem = (tetr_list*)malloc(sizeof(tetr_list*));
	if (new_elem)
	{
		new_elem->tetr = 0;
		new_elem->width = 0;
		new_elem->height = 0;
		new_elem->x = 0;
		new_elem->y = 0;
		new_elem->next = NULL;
	}
	return (new_elem);
}

tetr_list	*ft_list_push_back(tetr_list **begin_list)
{
	tetr_list	*new_last;
	tetr_list	*temp;

	temp = *begin_list;
	if (!temp)
	{
		*begin_list = ft_create_elem();
		new_last = *begin_list;
	}
	else
	{
		while (temp)
		{
			if (temp->next == NULL)
				break;
			temp = temp->next;
		}
		new_last = ft_create_elem();
		temp->next = new_last;
	}
	return (new_last);
}

void	ft_clean_list(tetr_list **begin_list)
{
	tetr_list	*temp;

	temp = *begin_list;
	while (temp)
	{
		temp->x = 0;
		temp->y = 0;
		temp = temp->next;
	}
}

void	ft_clean_arr(uint16_t *arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		arr[i++] = 0;
}

void bytes_to_left(tetr_list **list)
{
	tetr_list	*temp;
	short		i;

	temp = *list;
	while (temp)
	{
		while (!(temp->tetr & 61440))
			temp->tetr <<= 4;
		while (!(temp->tetr & 34952))
			temp->tetr <<= 1;
		i = 0;
		while (i < 4)
		{
			if (temp->tetr & (34952 >> i))
				(temp->width)++;
			if (temp->tetr & (61440 >> (i * 4)))
				(temp->height)++;
			i++;
		}
		temp = temp->next;
	}
}

int	str_to_bytes(char *str, tetr_list **list)
{
	int		k;
	int		size;
	tetr_list	*curr;

	size = 0;
	*list = NULL;
	while (*str)
	{
		k = 0;
		curr = ft_list_push_back(list);
		while (k++ < 16)
		{
			curr->tetr <<= 1;
			if (*str == '#')
				curr->tetr += 1;
			str++;
			while (*str != '#' && *str != '.' && *str)
				str++;
		}
		size++;
	}
	bytes_to_left(list);
	return (size);
}

int	ft_sqrt(int n)
{
	int i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

void print_map(tetr_list **list, int n)
{
	tetr_list	*temp;
	char		str[17][17];
	int			i;
	int			k;

	i = 0;
	while (i < n)
	{
		ft_memset(str[i], '.', (size_t)n);
		str[i++][n] = '\0';
	}
	k = 0;
	temp = *list;
	while (temp)
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

int	check_position(tetr_list *list, uint16_t *map, int n, short x)
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

void	clear_position(tetr_list **begin_list,
		tetr_list **list, uint16_t *map, int *n)
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
		*list = *begin_list;
		n++;
	}
}

int	solve_map(tetr_list **begin_list, int size)
{
	uint16_t	map[16];
	tetr_list	*list;
	int			i;
	int			n;

	i = 0;
	while (i < 16)
		map[i++] = 0;
	n = ft_sqrt(size * 4);
	list = *begin_list;
	while (list)
		if (!check_position(list, map, n, list->x))
			clear_position(begin_list, &list, map , &n);
		else
			list = list->next;
	return (n);
}

int main(void)
{
	tetr_list	*list;
	char 		str[232];
	int 		fd;
	int 		size;

	fd = open("test", O_RDONLY);
	read(fd, &str, 231);
	str[231] = '\0';
	size = str_to_bytes(str, &list);
	print_map(&list, solve_map(&list, size));
	return (0);
}
