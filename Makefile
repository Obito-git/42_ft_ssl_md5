NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -Iinc
SRC_PATH=src/
SRCS = $(SRC_PATH)main.c 
OBJ/OBJECTS		=	$(patsubst %.c, obj/%.o, $(SRCS))

all: $(NAME)
	
obj/%.o: %.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS)

obj:
	mkdir -p obj/$(SRC_PATH)

clean:
	rm -rf obj
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus