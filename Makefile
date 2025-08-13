CC:=cc
CFLAGS:= -Wextra -Wall -Werror -O3 -g
NAME:= minirt
INC = -I./includes
LIB = -L./mlx -L./libft -lft -lmlx_Linux -lXext -lX11 -lm -lpthread
BIN_DIR:=bin
SRC_DIRS= src $(patsubst %/, %, $(dir $(wildcard src/*/)))
SRC:= $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ:= $(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(SRC)))
LIBFT_PATH = ./libft/libft.a

vpath %.c $(SRC_DIRS)

all: $(NAME)

$(LIBFT_PATH):
	make all -C ./libft

$(NAME): $(OBJ) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ) $(LIB)

$(BIN_DIR)/%.o: %.c $(INCLUDES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean $(NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: all clean fclean re
.SECONDARY: