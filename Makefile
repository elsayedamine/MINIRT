NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra #-Werror
LIB_DIR = ./libft
lib = $(LIB_DIR)/libft.a

sources = \
		main.c \
		window.c \
		parsing.c \
		error.c \
		utils.c \
		get_color.c \
		fill_shapes.c \
		fill_settings.c \
		tokenizer.c \

object = $(sources:.c=.o)

all: $(NAME) 

$(lib):
	make all -C $(LIB_DIR)

$(NAME): $(object) $(lib)
	$(CC) $(CFLAGS) $(object) ./libft/libft.a -lmlx -lXext -lX11 -lm -o $(NAME)

clean:
	rm -rf $(object)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

flush:
	make re && make clean && clear && ./miniRT
.SECONDARY: $(object)
.PHONY: clean fclean re all