/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:17:49 by hstiv             #+#    #+#             */
/*   Updated: 2018/12/16 18:19:24 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
