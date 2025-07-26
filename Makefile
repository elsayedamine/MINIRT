NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIB_DIR = ./libft
lib = $(LIB_DIR)/libft.a

sources = \
		main.c \
		window.c \
		extraction/extraction.c \
		extraction/error.c \
		extraction/utils.c \
		extraction/get_color.c \
		extraction/fill_shapes.c \
		extraction/fill_settings.c \
		extraction/classifier.c \

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