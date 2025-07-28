NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I./includes
LIB = -L./mlx -L./libft -lft -lmlx_Linux -lXext -lX11 -lm
LIBFT_PATH = ./libft/libft.a

sources = \
		main.c \
		src/window.c \
		src/extraction/extraction.c \
		src/extraction/error.c \
		src/extraction/utils.c \
		src/extraction/get_color.c \
		src/extraction/fill_shapes.c \
		src/extraction/fill_settings.c \
		src/extraction/classifier.c \
		src/extraction/fillers.c \

object = $(sources:.c=.o)

all: $(NAME) 

$(LIBFT_PATH):
	make all -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(object) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(object) $(LIB) -o $(NAME)

clean:
	rm -rf $(object)
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean all

flush:
	make re && make clean && clear && ./miniRT
.SECONDARY: $(object)
.PHONY: clean fclean re all