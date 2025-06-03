CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

NAME = cub3D

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = 	./src/main.c \
		./src/init_info.c \
		./src/init_info_utils.c \
		./src/parse_col_tex.c \
		./src/check_map_char.c \
		./src/check_map_walls.c \
		./src/game.c \
		./src/game_utils.c \
		./src/DDA_algorithm.c \
		./src/draw_wall_line_1.c \
		./src/draw_wall_line_2.c \
		./src/handle_keys.c \
		./src/handle_scroll.c \
		./src/minimap.c \
		./src/bresenham.c \
		./src/utils.c \

OBJS = $(SRCS:.c=.o)

MINILIBX := ./MLX42/build
MLX_HEADERS := -I$(MINILIBX) -I./inc

LIBRARY := -L$(MINILIBX) -lmlx42 -ldl -lglfw -pthread -lm

all: $(NAME)

$(MINILIBX)/libmlx42.a:
	make -C $(MINILIBX)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)/libmlx42.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBRARY) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_HEADERS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

# Eliminar build
#  806  cmake -B build
#  808  cmake --build build -j4

#https://github.com/MariaAguiar/cub3D_invalid_map_tester
