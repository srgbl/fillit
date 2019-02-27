/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 20:01:14 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/24 20:05:01 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				fig_count(char *s)
{
	int			i;
	int			j;
	int			l;

	i = 0;
	l = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			l++;
		if (l == 4)
		{
			l = 0;
			j++;
			i++;
		}
		i++;
	}
	return (j);
}
