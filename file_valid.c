/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:58:42 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/24 18:23:25 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	grill_check(char *s, int grill)
{
	int		j;
	int		gl;

	j = 0;
	gl = grill;
	if (ft_strlen(s) == 4 && gl < 4)
	{
		while (s[j] != '\0')
		{
			if (s[j] == '#')
				gl++;
			j++;
		}
	}
	return (gl);
}

static int	whole_file_vl(char *ptr)
{
	int		i;
	int		l;

	i = ft_cntchr(ptr, '#');
	l = i / 4;
	if ((l * 4) != i)
		return (0);
	i = ft_cntchr(ptr, '.');
	l = i / 6;
	if ((l * 6) != i)
		return (0);
	return (1);
}

static int	splited_vl(char **s)
{
	int		grill;
	int		l;

	l = 0;
	grill = 0;
	while (s[l])
	{
		grill = grill_check(s[l], grill);
		if (grill < 4 && (ft_strlen(s[l]) != 4))
			return (0);
		if (ft_strlen(s[l]) != 4 || s[l][0] == '\0')
			grill = 0;
		l++;
	}
	return (1);
}

static int	not_split(char **s)
{
	int		l;

	l = mass_count(s);
	while (l > 0 && l > 4)
	{
		l = l - 5;
		if (s[l][0] != '\0')
			return (0);
	}
	ft_freeder(s);
	return (1);
}

int			file_valid(char *ptr)
{
	char	**s;
	int		i;

	i = whole_file_vl(ptr);
	if (i != 1)
		return (i);
	if (!(s = ft_strsplit_wtsp(ptr, '\n')))
		return (0);
	i = splited_vl(s);
	if (i != 1)
	{
		ft_freeder(s);
		return (0);
	}
	i = not_split(s);
	return (i);
}
