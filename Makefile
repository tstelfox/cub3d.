# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/01 11:53:24 by tmullan       #+#    #+#                  #
#    Updated: 2020/06/10 14:56:37 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = giza

MLX_DIR = ./mlx
GNL_DIR = ./gnl
LIBFT = ./libft

OBJ = cub3d.o cub_parser.o utils.o
	# testw.o
	# testl.o
	# testh.o
	# testw.o

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C $(GNL_DIR)
	make -C $(LIBFT)
	cp $(MLX_DIR)/libmlx.dylib .
	$(CC) $^ -Llibft -lft -Lgnl -lgnl  -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	
%.o: %.c
	$(CC) -Imlx -c $< -o $@

clean:
	# make clean -C $(MLX_DIR)
	# make clean -C $(GNL_DIR)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all












# $(NAME): $(OBJ)
# 	-L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
# 	make -C $(MLX_DIR)
# 	cp libmlx.dylib .
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@