/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:38:29 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/27 21:11:07 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

# define BUFF_SIZE 546

typedef	struct		s_tetr
{
	struct s_tetr	*next;
	uint16_t		tetr;
	short			width;
	short			height;
	short			x;
	short			y;
}					t_tetr;

int					grill_valid(char **s);
int					mass_count(char **s);
void				ft_freeder(char **s);
int					ft_cntchr(const char *ptr, int c);
void				ft_freeder_3(char ***s);
int					bmc(char **s);
int					fig_count(char *s);
int					file_valid(char *ptr);
int					figure_valid(char **str);
char				*filrd(char *file_name);
char				**ft_strsplit_wtsp(char const *s, char c);
char				***figure_split(char **str);
t_tetr				*ft_list_push_back(t_tetr **begin_list);
void				ft_clean_list(t_tetr **begin_list);
void				free_list(t_tetr *list);
void				ft_clean_arr(uint16_t *arr, int size);
int					str_to_bytes(char *str, t_tetr **list);
void				print_map(t_tetr **list, t_tetr *curr, int n);
int					ft_sqrt(int n);
int					solve_map(char *str);

#endif
