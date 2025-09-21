NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L$(MLX_DIR) -Lmlx -lmlx_Linux -lX11 -lXext

SRC_DIR = src
LIB_DIR = libs/libft
PARSE_DIR = parsing
WIN_DIR = window
ERRO_DIR = error
MLX_DIR = libs/mlx

MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT = $(LIB_DIR)/libft.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/$(ERRO_DIR)/ft_error.c \
	$(SRC_DIR)/$(ERRO_DIR)/ft_error2.c \
	$(SRC_DIR)/$(PARSE_DIR)/parsing.c \
	$(SRC_DIR)/$(PARSE_DIR)/read_file.c \
	$(SRC_DIR)/$(PARSE_DIR)/utilits.c \
	$(SRC_DIR)/$(PARSE_DIR)/input_verify.c \
	$(SRC_DIR)/$(PARSE_DIR)/data_verification.c \
	$(SRC_DIR)/$(PARSE_DIR)/utilits2.c \
	$(SRC_DIR)/$(PARSE_DIR)/flood_fill.c \
	$(SRC_DIR)/$(WIN_DIR)/ft_window.c \
	$(SRC_DIR)/$(WIN_DIR)/ft_mini_map.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)
# Trocar "tput clear || true" por clear
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@tput clear || true
	@echo "✅ ${NAME} is compiled."

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

val: $(NAME)
	valgrind --leak-check=full ./$(NAME) $(ARGS)

$(LIBFT):
	@make -C $(LIB_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -f $(OBJS)
	@clear
	@echo "🗑️ Objects removed."

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@clear
	@echo "🗑️ Program and objects removed."

re: fclean all
