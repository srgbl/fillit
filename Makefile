
NAME = fillit
SRC = fillit.c
OBJECTS = fillit.o

all: $(NAME)

$(NAME): $(SRC)
	clang -Wall -Wextra -Werror -I libft/includes -c $(SRC) -o $(OBJECTS)
	clang -o $(NAME) $(OBJECTS) -L libft/ -lft

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all
