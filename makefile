NAME        =   so_long

CC          =   clang
CFLAGS      =   -Wall -Wextra -Werror -g

LIBFT_PATH	=	./libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_FILE	=	libmlx.a
MLX_FLAG    =   -lX11 -lXext
MLX_PATH	=	./src/mlx/
MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))
MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

SRC_DIR		=	./src/
INC_DIR		=	./include/

# Fichiers sources
SO_LONG_FILE =  main.c \
				mouvement.c \
				map.c \
				verif_map.c \
				verif_elt.c \
				read_map.c \
				verif_chemin.c \
				exit.c \

SRC = $(addprefix $(SRC_DIR),$(SO_LONG_FILE))
OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)


prepare:
	-@git clone https://github.com/42Paris/minilibx-linux.git src/mlx
	@echo "MiniLibX cloned into $(MLX_PATH)\n"

lib: prepare
	@echo "COMPILING $(LIBFT_PATH)\n"
	@make -C $(LIBFT_PATH)
	@echo "LIBFT_lib created\n"

mlx: $(MLX_PATH)
	@echo "COMPILING MiniLibX in $(MLX_PATH)...\n"
	@$(MAKE) -C $(MLX_PATH)
	@echo "MLX_lib created\n"

$(NAME): lib mlx $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_EX) -o $(NAME)
	@echo "./so_long created\n"

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ)
	@echo "Deleting objects in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@rm -rf $(MLX_PATH)
	make -C ./src/mlx clean

re: fclean all

.PHONY: all clean fclean re