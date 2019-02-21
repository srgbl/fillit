#include <unistd.h>
#include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void bytes_to_left(unsigned short *tetr, int size)
{
	int i;

	i = 0;
	while(i < size)
	{
		while (!(tetr[i] & 61440))
			tetr[i] <<= 4;
		while (!(tetr[i] & 34952))
			tetr[i] <<= 1;
		i++;
	}
}

int	str_to_bytes(char *str, unsigned short *tetr)
{
	int i;
	int k;
	int l;

	i = 0;
	l = 0;
	while(str[i])
	{
		k = 0;
		while (k < 16)
		{
			tetr[l] <<= 1;
			if (str[i] == '#')
				tetr[l] += 1;
			i++;
			k++;
			while (str[i] == '\n')
				i++;
		}
		l++;
	}
	return(l);
}

int	ft_sqrt(short n)
{
	int i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

void	t_map(unsigned short *tetr, short size)
{
	unsigned int map[26];
	int i;
	int n;

	i = 0;
	while (i < 26)
		map[i++] = 0;
	n = ft_sqrt(size * 4);
	printf ("n = %d\n", n);
	i = 0;
	while(i < n)
	{
		printf("%d\n", tetr[i]);
		i++;
	}
}
int main(void)
{
	char str[101];
	int fd;
	unsigned short tetr[26];
	short size;

	fd = open("test", O_RDONLY);
	read(fd, &str, 100);

	size = str_to_bytes(str, tetr);
	bytes_to_left(tetr, size);
	t_map(tetr, size);
	return (0);
}
