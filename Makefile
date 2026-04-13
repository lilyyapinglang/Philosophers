NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP

SRCS := main.c utils.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

RM := rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(SRCS:.c=.d)