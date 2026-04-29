NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror #-MMD -MP

SRC_DIR := src

SRCS := \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/input_valid_check.c \
    $(SRC_DIR)/init.c \
    $(SRC_DIR)/routine.c \
    $(SRC_DIR)/routine_details.c \
    $(SRC_DIR)/monitor.c \
    $(SRC_DIR)/log.c \
    $(SRC_DIR)/utils.c

OBJ_DIR := obj
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
