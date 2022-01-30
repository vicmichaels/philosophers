NAME = philo_bonus

HEAD = ./inc/philosophers.h
SRC_DIR = ./src/
SRC_FILES = ft_forks.c ft_game.c ft_message.c ft_utils1.c main.c
SRC = $(SRC_DIR) $(SRC_FILES)

OBJ_DIR = obj/
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

CC = gcc
FLAGS = -Wall -Werror -Wextra -pthread
INC = ./inc/

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) CREATED!$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)CLEAR!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)EXTRA CLEAR!$(RESET)"

re: fclean all