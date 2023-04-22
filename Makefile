NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -Iinc -Iinc/algorithms

SRC_PATH=src/
ALGO_PATH=$(SRC_PATH)algorithms/
UTILS_PATH=$(SRC_PATH)utils/
OBJ_PATH=obj/

SRCS = $(SRC_PATH)main.c $(ALGO_PATH)config.c $(ALGO_PATH)sha256.c \
		$(UTILS_PATH)ft_strlen.c
OBJ/OBJECTS		=	$(patsubst %.c, obj/%.o, $(SRCS))

all: $(NAME)
	
obj/%.o: %.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS)

obj:
	mkdir -p $(OBJ_PATH)$(ALGO_PATH)
	mkdir -p $(OBJ_PATH)$(UTILS_PATH)

clean:
	rm -rf $(OBJ_PATH)
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus