/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:58:13 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/24 15:54:10 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

static char		**fv2(char **str, int j)
{
	int			i;
	char		**s;

	i = 0;
	if (!(s = (char **)malloc(sizeof(char *) * 5)))
		return (NULL);
	while (i < 4)
	{
		if (!(s[i] = ft_strdup(str[j])))
			return (NULL);
		i++;
		j++;
	}
	s[4] = NULL;
	return (s);
}

char			***figure_split(char **str)
{
	int			i;
	int			e;
	char		***s;

	i = 0;
	e = 0;
	if (!(s = (char ***)malloc(sizeof(char **) * (bmc(str) + 1))))
		return (NULL);
	while (e < bmc(str))
	{
		if (!(s[e] = fv2(str, i)))
		{
			ft_freeder_3(s);
			return (NULL);
		}
		i = i + 5;
		e++;
	}
	s[e] = NULL;
	return (s);
}
