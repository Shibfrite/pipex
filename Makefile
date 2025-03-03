NAME			:= pipex
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror -g
INC_DIR			:= includes
SRC_DIR			:= srcs
BONUS_DIR		:= srcs_bonus
OBJ_DIR			:= objs
BONUS_OBJ_DIR   := objs_bonus
LIBFT_DIR		:= libft
SRC_FILES		:= main.c support.c exec.c token.c
BONUS_FILES		:= main.c support.c heredoc.c pipes.c fork.c
SRC_PREFIX		:= $(SRC_DIR)/
BONUS_PREFIX	:= $(BONUS_DIR)/
SRCS			:= $(addprefix $(SRC_PREFIX),$(SRC_FILES))
BONUS_SRCS		:= $(addprefix $(BONUS_PREFIX),$(BONUS_FILES))
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS		:= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)
INC				:= -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)
LIBFT			:= $(LIBFT_DIR)/libft.a
DIRS			:= $(INC_DIR) $(SRC_DIR) $(OBJ_DIR) $(BONUS_OBJ_DIR) $(LIBFT_DIR)

all:			$(NAME)

bonus:		  $(BONUS_OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
		echo "$(NAME) with bonus created successfully!"

$(NAME):		$(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@
		echo "$(NAME) created successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(DIRS)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

RM			  := rm -rf

$(DIRS):
		mkdir -p $@
		echo "Created directory: $@"

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR) -s

clean:
		echo "Cleaning object files..."
		$(RM) $(OBJ_DIR) $(BONUS_OBJ_DIR)
		$(MAKE) -C $(LIBFT_DIR) -s clean
		echo "Object files cleaned."

fclean: clean
		echo "Cleaning executable and library..."
		$(RM) $(NAME) $(NAME)_bonus
		$(MAKE) -C $(LIBFT_DIR) -s fclean
		echo "Executable and library cleaned."

re: fclean all

.SILENT:
.PHONY: all clean fclean re bonus
