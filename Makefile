
NAME = fillit
SRC = fillit.c
OBJECTS = fillit.o

all: $(NAME)

$(NAME): $(SRC)
	clang -Wall -Wextra -Werror -I libft/includes -o $(OBJECTS) -c $(SRC) -g
	clang -o $(NAME) $(OBJECTS)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all
