NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes
CCFLAGS = -pthread
SRC_PATH = src
SRC_FILES =	main.c			valider_args.c			utils.c			\
			affichage_message.c		la_vie.c			philo_utils.c
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ_FILES = $(SRC_FILES:%.c=%.o)
OBJ = $(addprefix $(SRC_PATH)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(CCFLAGS) $^ -o $@

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
