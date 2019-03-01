/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grill_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:11 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/27 19:24:24 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	grill(char **s, int j)
{
	int		k;
	int		l;

	k = 0;
	l = 0;
	while (s[j][k] != '\0')
	{
		if (s[j][k] == '#')
			l++;
		k++;
	}
	return (l);
}

static int	dots(char **s, int j)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (s[j][k] != '\0')
	{
		if (s[j][k] == '.')
			i++;
		k++;
	}
	return (i);
}

int			grill_valid(char **s)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	while (s[j] != NULL)
	{
		i = i + grill(s, j);
		l = l + dots(s, j);
		if (((s[j + 1] == NULL) || s[j][0] == '\0') &&
				(i != 4 || l != 12))
			return (0);
		if (s[j][0] == '\0')
		{
			i = 0;
			l = 0;
		}
		j++;
	}
	return (1);
}
