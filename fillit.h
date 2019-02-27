/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:38:29 by hstiv             #+#    #+#             */
/*   Updated: 2019/02/27 03:46:09 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include <libft.h>
# include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

# define BUFF_SIZE 546

typedef struct		m_list
{
	struct m_list	*next;
	uint16_t		tetr;
	short			z;
	int				w;
	short			width;
	short			height;
	short			x;
	short			y;
}					tetr_list;

int				mass_count(char **s);
void			ft_freeder(char **s);
int				ft_cntchr(const char *ptr, int c);
void			ft_freeder_3(char ***s);
int				bmc(char **s);
int				fig_count(char *s);
int				file_valid(char *ptr);
int				figure_valid(char **str);
char			*filrd(char *file_name);
char			**ft_strsplit_wtsp(char const *s, char c);
char			***figure_split(char **str);

tetr_list		*ft_list_push_back(tetr_list **begin_list);
void			ft_clean_list(tetr_list **begin_list);
void			free_list(tetr_list	*list);
void			ft_clean_arr(uint16_t *arr, int size);
int				str_to_bytes(char *str, tetr_list **list);
int				ft_sqrt(int n);
int				solve_map(char *str);

#endif
