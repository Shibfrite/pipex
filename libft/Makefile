# ==========================
# Project Name
# ==========================
NAME        := libft.a

# ==========================
# Compiler and Flags
# ==========================
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror

# ==========================
# Directory Paths
# ==========================
INC_DIR     := includes
SRC_DIR     := srcs
DLIST_DIR   := srcs/dlist
LIST_DIR    := srcs/list
MEMORY_DIR  := srcs/memory
PRINT_DIR   := srcs/print
STR_DIR     := srcs/str
HASH_DIR    := srcs/hash_table
OBJ_DIR     := objs
OBJ_SUBDIRS := $(OBJ_DIR)/dlist $(OBJ_DIR)/list $(OBJ_DIR)/memory $(OBJ_DIR)/print $(OBJ_DIR)/str $(OBJ_DIR)/hash_table

# ==========================
# Source Files
# ==========================
DLIST_FILES := \
    ft_dlstadd_back.c ft_dlstadd_front.c ft_dlstclear.c ft_dlstdelone.c \
    ft_dlstiter.c ft_dlstlast.c ft_dlstmap.c ft_dlstnew.c ft_dlstsize.c \
    ft_dlst_rotate.c

LIST_FILES  := \
    ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
    ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

MEMORY_FILES := \
    ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
    ft_memmove.c ft_memset.c

PRINT_FILES := \
    ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c

STR_FILES   := \
	ft_atoi.c ft_isprint.c ft_strdup.c ft_strlen.c ft_strtrim.c \
	ft_isalnum.c ft_itoa.c ft_striteri.c ft_strmapi.c ft_substr.c \
	ft_isalpha.c ft_split.c ft_strjoin.c ft_strncmp.c ft_tolower.c \
	ft_isascii.c ft_strchr.c ft_strlcat.c ft_strnstr.c ft_toupper.c \
	ft_isdigit.c ft_strcmp.c ft_strlcpy.c ft_strrchr.c \
	is_sign.c is_space.c skip.c

HASH_FILES  := \
    hash_table.c hash_functions.c collision_resolution.c utility.c

# Add prefixes for each directory to the respective files
SRCS        := $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
               $(addprefix $(DLIST_DIR)/, $(DLIST_FILES)) \
               $(addprefix $(LIST_DIR)/, $(LIST_FILES)) \
               $(addprefix $(MEMORY_DIR)/, $(MEMORY_FILES)) \
               $(addprefix $(PRINT_DIR)/, $(PRINT_FILES)) \
               $(addprefix $(STR_DIR)/, $(STR_FILES))  \
               $(addprefix $(HASH_DIR)/, $(HASH_FILES))

# ==========================
# Object Files
# ==========================
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ==========================
# Include Paths
# ==========================
INC         := -I$(INC_DIR)

# ==========================
# Default Target
# ==========================
all: $(OBJ_SUBDIRS) $(NAME)

# ==========================
# Build the Library
# ==========================
$(NAME): $(OBJS)
	echo "Linking $(NAME)..."
	ar -rc $@ $^
	ranlib $@
	echo "$(NAME) created successfully!"

# ==========================
# Compile Source Files to Object Files
# ==========================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_SUBDIRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ==========================
# Create Necessary Directories
# ==========================
$(OBJ_SUBDIRS):
	mkdir -p $@

# ==========================
# Clean Object Files and Directories
# ==========================
clean:
	echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	echo "Object files cleaned."

# ==========================
# Clean Library Files
# ==========================
fclean: clean
	echo "Cleaning library..."
	rm -f $(NAME)
	echo "Library cleaned."

# ==========================
# Rebuild Everything from Scratch
# ==========================
re: fclean all

.SILENT:
.PHONY: all clean fclean re bonus
