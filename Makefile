# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/01 11:53:24 by tmullan       #+#    #+#                  #
#    Updated: 2020/08/10 18:53:58 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX_DIR = ./mlx
GNL_DIR = ./gnl
LIBFT = ./libft

OBJ = cub3d.o cub_parser.o utils.o mlx_start.o raycaster.o sprite.o \
		sprite_draw.o quit.o bmp.o validator.o pixel_put_n_get.o \
		movement.o keys.o drawline.o \
		map_check.o split_extra.o utils_texget.o player_n_res.o

FLAGS = -Wall -Wextra -Werror -O3 #-fsanitize=address -g -fno-omit-frame-pointer

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C $(GNL_DIR)
	make -C $(LIBFT)
	cp $(MLX_DIR)/libmlx.dylib .
	$(CC) $^ -Llibft -lft -Lgnl -lgnl  -Lmlx -lmlx -framework OpenGL \
			-framework AppKit -o $(NAME) $(FLAGS)

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

clean:
	make clean -C $(MLX_DIR)
	make clean -C $(GNL_DIR)
	make clean -C $(LIBFT)
	rm -f $(OBJ)
	rm -f screenshot.bmp

fclean: clean
	rm -f $(NAME)

re: fclean all
