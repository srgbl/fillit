#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct		s_list
{
	uint16_t		tetr;
	short			width;
	short			height;
	short			x;
	short			y;
	struct s_list	*next;
}					t_list;

void bytes_to_left(t_list **list)
{
	t_list	*temp;
	short 	i;

	temp = *list;
	while(temp)
	{
		while (!(temp->tetr & 61440))
			temp->tetr <<= 4;
		while (!(temp->tetr & 34952))
			temp->tetr <<= 1;
		i = 0;
		while (i < 4)
		{
			if (temp->tetr & (34952 >> i))
				temp->width++;
			if (temp->tetr & (61440 >> (i * 4)))
				temp->height++;
			i++;
		}
		temp = temp->next;
	}
}

t_list	*ft_create_elem()
{
	t_list	*new_elem;

	new_elem = (t_list*)malloc(sizeof(t_list*));
	if (new_elem)
	{
		new_elem->tetr = 0;
		new_elem->width = 0;
		new_elem->height = 0;
		new_elem->x = 0;
		new_elem->y = 0;
		new_elem->next = NULL;
	}
	return (new_elem);
}

void	ft_clean_list(t_list **begin_list)
{
	t_list	*temp;

	temp = *begin_list;
	while (temp)
	{
		temp->x = 0;
		temp->y = 0;
		temp = temp->next;
	}
}
void	ft_clean_arr(uint16_t *arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		arr[i++] = 0;
}

t_list	*ft_list_push_back(t_list **begin_list)
{
	t_list	*new_last;
	t_list	*temp;

	temp = *begin_list;
	if (temp == NULL)
	{
		*begin_list = ft_create_elem();
		new_last = *begin_list;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		new_last = ft_create_elem();
		temp->next = new_last;
	}
	return(new_last);
}

int	str_to_bytes(char *str, t_list **list)
{
	int		i;
	int		k;
	int		size;
	t_list	*curr;

	i = 0;
	size = 0;
	while(str[i])
	{
		k = 0;
		curr = ft_list_push_back(list);
		while (k < 16)
		{
			curr->tetr <<= 1;
			if (str[i] == '#')
				curr->tetr += 1;
			i++;
			k++;
			while (str[i] != '#' && str[i] != '.' && str[i])
				i++;
		}
		size++;
	}
	return(size);
}

int	ft_sqrt(int n)
{
	int i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

void print_map(t_list **list, int size)
{
	t_list	*temp;
	char	str[17][17] = {0};
	int		i;
	int 	k;

	i = 0;
	while (i < size)
	{
		k = 0;
		while(k < size)
			str[i][k++] = '.';
		i++;
	}
	k = 0;
	temp = *list;
	while (temp)
	{
		i = 0;
		while (i < 16)
		{
			if (temp->tetr & (1 << (15 - i)))
				str[temp->y + i / 4][temp->x + i % 4] = 'A' + k;
			i++;
		}
		k++;
		temp = temp->next;
	}
	i = 0;
	while (i < size)
		printf("%s\n", str[i++]);
}

int	t_map(t_list **begin_list, int size)
{
	uint16_t	map[16];
	t_list		*list;
	t_list		*temp;
	int			i;
	int			n;
	int			x;
	int			y;
	int			next;

	i = 0;
	while (i < 16)
		map[i++] = 0;
	n = ft_sqrt(size * 4);
	list = *begin_list;
	while (list)
	{
		next = 0;
		y = list->y;
		while (y + list->height <= n)
		{
			x = list->x;
			while (x + list->width <= n)
			{
				if (next)
					break ;
				i = 0;
				while (i < 4 && !(((list->tetr << (i * 4) & 61440 ) >> x ) & map[y + i]))
					i++;
				if (i == 4)
				{
					list->x = x;
					list->y = y;
					i = 0;
					while (i < 4)
					{
						map[y + i] |= (list->tetr << (i * 4) & 61440) >> x;
						i++;
					}
					print_map(begin_list, 16);
					next = 1;
					break ;
				}
				else
					x++;
			}
			if (next)
					break ;
			y++;
		}
		if (!next)
		{
			list->x = 0;
			list->y = 0;
			temp = *begin_list;
			while (temp->next != list)
				temp = temp->next;
			list = temp;
			i = 0;
			while (i < 4)
			{
				map[list->y + i] ^= list->tetr << (i * 4) & 61440 >> list->x;
				i++;
			}
			list->x += 1;
			if (list->x + list->width > n)
			{
				list->x = 0;
				list->y += 1;
				if (list->y + list->height > n)
				{
					ft_clean_list(begin_list);
					ft_clean_arr(map, 16);
					list = *begin_list;
					n++;
				}
			}
		}
		else
		{
			list = list->next;
			printf("\nn = %d\n", n);
		//	print_map(begin_list, 16);
		}
	}
	return (n);
}

int main(void)
{
	char str[101];
	int fd;
	t_list	*list;
	int size;

	fd = open("test", O_RDONLY);
	read(fd, &str, 100);

	size = str_to_bytes(str, &list);
	bytes_to_left(&list);
	printf("\nres = %d\n", t_map(&list, size));
	print_map(&list, 16);
	return (0);
}
