NAME = ft_ssl
CC = gcc

SRC_PATH=src/
ALGO_PATH=$(SRC_PATH)algorithms/
OBJ_PATH=obj/
LIBS_PATH=libs/

LIBFT_PATH = $(LIBS_PATH)/libft
LIBFT_NAME = libft.a

CFLAGS = -Wall -Werror -Wextra -g3 -Iinc -Iinc/algorithms -I$(LIBFT_PATH)/includes

SRCS =  $(wildcard $(ALGO_PATH)*.c) \
		$(SRC_PATH)main.c $(SRC_PATH)exit_error.c $(SRC_PATH)source_processing.c $(SRC_PATH)data_processing.c
OBJ/OBJECTS		=	$(patsubst %.c, obj/%.o, $(SRCS))

all: $(NAME)
	
obj/%.o: %.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(LIBFT_NAME) $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LIBFT_NAME)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH) && cp -f $(LIBFT_PATH)/$(LIBFT_NAME) $(shell pwd)

obj:
	mkdir -p $(OBJ_PATH)$(ALGO_PATH)

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -rf $(LIBFT_NAME)
	rm -rf $(OBJ_PATH)
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus