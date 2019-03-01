/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bytes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:55:13 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/27 21:10:44 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	bytes_to_left(t_tetr **list)
{
	t_tetr	*temp;
	int		i;

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

int		str_to_bytes(char *str, t_tetr **list)
{
	int		k;
	int		size;
	t_tetr	*curr;

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

int		ft_sqrt(int n)
{
	int	i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

void	print_map(t_tetr **list, t_tetr *curr, int n)
{
	t_tetr	*temp;
	char	str[17][17];
	int		i;
	int		k;

	i = 0;
	while (i < n)
	{
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
