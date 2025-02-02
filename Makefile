NAME		:= pipex

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g

INC_DIR 	:= includes
SRC_DIR 	:= srcs
OBJ_DIR		:= objs
LIBFT_DIR	:= libft

SRC_FILES   := main.c 
SRC_PREFIX  := $(SRC_DIR)/
SRCS        := $(addprefix $(SRC_PREFIX),$(SRC_FILES))

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INC			:= -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)
LIBFT		:= $(LIBFT_DIR)/libft.a

DIRS		:= $(INC_DIR) $(SRC_DIR) $(OBJ_DIR) $(LIBFT_DIR)

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@
	echo "$(NAME) created successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

RM			:= rm -rf

$(DIRS):
	mkdir -p $@
	echo "Created directory: $@"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) -s

clean:
	echo "Cleaning object files..."
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) -s clean
	echo "Object files cleaned."

fclean: clean
	echo "Cleaning executable and library..."
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) -s fclean
	echo "Executable and library cleaned."

re: fclean all

.SILENT:
.PHONY: all clean fclean re
