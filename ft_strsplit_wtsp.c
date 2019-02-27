/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_wtsp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:13:04 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/23 18:02:58 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static	char		**ft_splitter(char **argv, const char *s, char c)
{
	int				i;

	i = 0;
	while (*s != '\0')
	{
		while (*s != c && *s != '\0')
		{
			if (!(argv[i] = ft_strsub(s, 0, 4)))
			{
				ft_freeder(argv);
				return (NULL);
			}
			s += 5;
			i++;
		}
		while (*s == c && *s != '\0')
		{
			argv[i] = ft_strnew(1);
			i++;
			s++;
		}
	}
	argv[i] = NULL;
	return (argv);
}

char				**ft_strsplit_wtsp(char const *s, char c)
{
	char			**argv;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	i = ft_cntchr(s, c);
	if (!(argv = (char **)malloc(sizeof(char *) * (i + 1))))
	{
		free(argv);
		return (NULL);
	}
	return (ft_splitter(argv, s, c));
}
