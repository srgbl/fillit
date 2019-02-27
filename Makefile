NAME = fillit

SRCS = main.c ft_solver.c ft_lists.c ft_bytes.c fig_count.c ft_freeder_3.c figure_split.c bmc.c \
	file_valid.c figure_valid.c filrd.c ft_strsplit_wtsp.c \
	mass_count.c ft_cntchr.c ft_freeder.c $(LFT)

LFT = libft/libft.a

HEADER = libft/includes

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft re && gcc -o $(NAME) $(FLAGS) $(SRCS) -I $(HEADER)

norm:
	norminette main.c figure_split.c bmc.c ft_freeder_3.c file_valid.c \
	filrd.c ft_strsplit_wtsp.c fillit.h fig_count.c ft_solver.c ft_lists.c ft_bytes.c

clean:
	rm -f *.o
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
