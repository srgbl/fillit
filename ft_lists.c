/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:37:38 by slindgre          #+#    #+#             */
/*   Updated: 2019/02/27 20:37:03 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		free_list(t_tetr *list)
{
	t_tetr	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

t_tetr		*ft_create_elem(void)
{
	t_tetr	*new_elem;

	new_elem = malloc(sizeof(t_tetr));
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

t_tetr		*ft_list_push_back(t_tetr **begin_list)
{
	t_tetr	*new_last;
	t_tetr	*temp;

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
				break ;
			temp = temp->next;
		}
		new_last = ft_create_elem();
		temp->next = new_last;
	}
	return (new_last);
}

void		ft_clean_list(t_tetr **begin_list)
{
	t_tetr	*temp;

	temp = *begin_list;
	while (temp)
	{
		temp->x = 0;
		temp->y = 0;
		temp = temp->next;
	}
}

void		ft_clean_arr(uint16_t *arr, int size)
{
	int		i;

	i = 0;
	while (i < size)
		arr[i++] = 0;
}
