CC:= cc
CFLAGS:= -Wall -Wextra -Werror -Ofast
NAME:= minirt
INC= -I./includes
LIB= -L./mlx -L./libft -lft -lmlx -lXext -lX11 -lm
LIBFT_PATH= ./libft/libft.a
BIN_DIR:=bin
SRC:= 	src/main.c \
		src/window.c \
		src/extraction/classifier.c \
		src/extraction/error.c \
		src/extraction/extraction.c \
		src/extraction/extract_texture.c \
		src/extraction/fill_cone.c \
		src/extraction/fill_cylinder.c \
		src/extraction/fillers.c \
		src/extraction/fill_plane.c \
		src/extraction/fill_rectangle.c \
		src/extraction/fill_settings.c \
		src/extraction/fill_sphere.c \
		src/extraction/get_color.c \
		src/extraction/object.c \
		src/intersections/cone.c \
		src/intersections/cylinder.c \
		src/intersections/plane.c \
		src/intersections/rectangle.c \
		src/intersections/sphere.c \
		src/raytracing/compute_light.c \
		src/raytracing/draw.c \
		src/raytracing/init.c \
		src/raytracing/rays.c \
		src/raytracing/texture_getters.c \
		src/raytracing/textures.c \
		src/transformations/camera.c \
		src/transformations/hooks.c \
		src/transformations/shapes.c \
		src/utils/color.c \
		src/utils/rotate.c \
		src/vector/op.c \
		src/vector/vector_op2.c \
		src/vector/vector_op.c

OBJ:= $(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(SRC)))

vpath %.c $(dir $(SRC))

all: $(NAME)

$(LIBFT_PATH):
	make all -C ./libft

$(NAME): $(OBJ) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ) $(LIB)

$(BIN_DIR)/%.o: %.c $(INCLUDES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(BIN_DIR)
	make clean -C libft

fclean: 
	rm -rf $(BIN_DIR)
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean $(NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: all clean fclean re
.SECONDARY: