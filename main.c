/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:59:35 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/27 03:38:17 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	char	*s;

	if (argc == 2)
	{
		if ((s = filrd(argv[1])) == NULL)
		{
			ft_putstr("error\n");
			return (0);
		}
		solve_map(s);
		free(s);
	}
	if (argc != 2)
		ft_putstr("usage: fillit source_file\n");
	return (0);
}

