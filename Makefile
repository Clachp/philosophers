NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror  -g3 -pthread

#CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3 -pthread

SRCS = main.c \
	init.c \
	utils.c \
	routines_utils.c \
	routines.c

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "philo..."

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Philo is clean"

fclean:
	@make --no-print-directory clean
	@rm -rf $(NAME)

re: fclean
	@make --no-print-directory all

.PHONY: all clean fclean re bonus

#.SILENT: