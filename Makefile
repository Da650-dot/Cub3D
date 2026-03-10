# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/20 00:00:00 by student           #+#    #+#              #
#    Updated: 2026/02/20 00:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
BONUS_NAME  = .bonus_done

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O2
INCLUDES    = -I./includes -I./libft -I./mlx

SRC_DIR     = src
OBJ_DIR     = obj

SRC =   $(SRC_DIR)/main.c \
        $(SRC_DIR)/init.c \
        $(SRC_DIR)/parse/parse.c \
        $(SRC_DIR)/parse/parse_map.c \
        $(SRC_DIR)/parse/parse_textures.c \
        $(SRC_DIR)/raycasting/raycasting.c \
        $(SRC_DIR)/raycasting/calc_wall.c \
        $(SRC_DIR)/raycasting/render.c \
        $(SRC_DIR)/player/movement.c \
        $(SRC_DIR)/player/keys.c \
        $(SRC_DIR)/utils/error.c \
        $(SRC_DIR)/utils/free.c \
        $(SRC_DIR)/helpers/init_helpers.c \
        $(SRC_DIR)/helpers/parse_helpers.c \
        $(SRC_DIR)/helpers/error_helpers.c


SRC_BONUS = $(SRC_DIR)/main_bonus.c \
        $(SRC_DIR)/init.c \
        $(SRC_DIR)/parse/parse.c \
        $(SRC_DIR)/parse/parse_map.c \
        $(SRC_DIR)/parse/parse_textures.c \
        $(SRC_DIR)/raycasting/raycasting.c \
        $(SRC_DIR)/raycasting/calc_wall.c \
        $(SRC_DIR)/bonus/render_bonus.c \
        $(SRC_DIR)/bonus/movement_bonus.c \
        $(SRC_DIR)/utils/error.c \
        $(SRC_DIR)/utils/free.c \
        $(SRC_DIR)/bonus/minimap.c \
        $(SRC_DIR)/bonus/door.c \
        $(SRC_DIR)/bonus/mouse.c \
        $(SRC_DIR)/bonus/bullet.c \
        $(SRC_DIR)/bonus/bullet_move.c \
        $(SRC_DIR)/bonus/keys_bonus.c \
        $(SRC_DIR)/helpers/init_helpers.c \
        $(SRC_DIR)/helpers/parse_helpers.c \
        $(SRC_DIR)/helpers/error_helpers.c

OBJ         = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS   = $(SRC_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
MLX_DIR     = mlx
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) mlx_build
	@rm -f $(BONUS_NAME)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "\033[0;32m[OK] $(NAME) mandatory compiled!\033[0m"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJ_BONUS) $(LIBFT) mlx_build
	@rm -f $(NAME)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@touch $(BONUS_NAME)
	@echo "\033[0;32m[OK] $(NAME) bonus compiled!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

mlx_build:
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) 2>/dev/null || true; fi

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(BONUS_NAME)
	@echo "\033[0;33m[CLEAN] objects removed\033[0m"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "\033[0;31m[FCLEAN] $(NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus mlx_build