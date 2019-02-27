/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filrd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:10:56 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/27 00:30:32 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char		*filrd(char *file_name)
{
	int		fd;
	int		y;
	char	**s;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	if (!(fd = open(file_name, O_RDONLY)))
		return (NULL);
	if ((y = read(fd, buf, BUFF_SIZE)) < 0)
		return (NULL);
	buf[y] = '\0';
	if (file_valid(buf) != 1)
		return (NULL);
	if (!(s = ft_strsplit_wtsp(buf, '\n')))
		return (NULL);
	if (figure_valid(s) != 1)
	{
		ft_freeder(s);
		return (NULL);
	}
	ft_freeder(s);
	str = ft_strdup(buf);
	return (str);
}
