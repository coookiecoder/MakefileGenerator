SRC = main.c 
OBJ = main.o 

NAME = MakefileGenerator

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re debug
