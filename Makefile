CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

NAME = cub3D

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = 	./src/main.c \
		./src/init_info.c \
		./src/check_map.c \

OBJS = $(SRCS:.c=.o)

MINILIBX := ./MLX42/build
MLX_HEADERS := -I$(MINILIBX) -I./inc

LIBRARY := -L$(MINILIBX) -ldl -lglfw -pthread -lm

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


#cositaass a probar
#https://github.com/MariaAguiar/cub3D_invalid_map_tester (mirar tb color y texture)
#	fail: el mapa es lo ultimo (como esta bien identificado no da error/
#		 el identificador solo, sin espacio tb da error)
#	fail1: solo esta el mapa
#	fail2: falta el mapa
#	fail3: mas de 1 jugador
#	fail4: falta jugador
#	fail5: archivo vacio
#	fail6: linea vacia/islas
#	fail7: solo 1
#	fail8: jugador fuera mapa
