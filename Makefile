NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
LIB_DIR = lib
PARSE_DIR = parsing
ERRO_DIR = error

LIBFT = $(LIB_DIR)/libft.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/$(ERRO_DIR)/ft_error.c \
	$(SRC_DIR)/$(PARSE_DIR)/parsing.c \
	$(SRC_DIR)/$(PARSE_DIR)/read_file.c \
	$(SRC_DIR)/$(PARSE_DIR)/utilits.c \
	$(SRC_DIR)/$(PARSE_DIR)/input_verify.c \
	$(SRC_DIR)/$(PARSE_DIR)/data_verification.c \
	$(SRC_DIR)/$(PARSE_DIR)/utilits2.c \
	$(SRC_DIR)/$(PARSE_DIR)/rgb.c \
	$(SRC_DIR)/$(PARSE_DIR)/flood_fill.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)
# Trocar "tput clear || true" por clear
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@tput clear || true
	@echo "✅ ${NAME} is compiled."

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

val: $(NAME)
	valgrind --leak-check=full ./$(NAME) $(ARGS)

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJS)
	@clear
	@echo "🗑️ Objects removed."

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@clear
	@echo "🗑️ Program and objects removed."

re: fclean all

test: $(NAME)
	@echo "🧪 Rodando testes localmente..."
	@chmod +x tests/run_tests.sh
	@tests/run_tests.sh

docker-test:
	@echo "🐳 Rodando testes no Docker..."
	@docker build -t cub3d-tests .
	@docker run --rm cub3d-tests tests/run_tests.sh
	@docker rmi cub3d-tests

.PHONY: all clean fclean re val test docker-test
