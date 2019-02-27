/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bytes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:39:08 by slindgre          #+#    #+#             */
/*   Updated: 2019/02/27 01:39:08 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void bytes_to_left(tetr_list **list)
{
	tetr_list	*temp;
	int			i;

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
