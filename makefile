# Name
NAME	= minishell

# Compiler and Flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -MMD -MP

# OS-specific flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    # macOS settings
	CPPFLAGS += -I/opt/homebrew/opt/readline/include
	LDFLAGS = -L/opt/homebrew/opt/readline/lib
else
    # Linux settings
	CPPFLAGS += -I/usr/include/readline
	LDFLAGS = -L/usr/lib
endif

LINKS = -lft -lreadline

# Libft
LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a
LIBFT			= $(LIBFT_DIR)$(LIBFT_NAME)

# Includes
INC	=	-I ./includes/header_mig.h \
		-I ./libft/includes \
		$(CPPFLAGS)

# Source files
SRC_DIR	=	sources/
SRC_SUBDIRS	=  $(shell find $(SRC_DIR) -type d)
SRC := $(foreach dir, $(SRC_SUBDIRS), $(wildcard $(dir)/*.c))

# Object files
OBJ_DIR	= obj/
OBJ		= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# Build rules
all:			$(LIBFT) $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
				@echo "Making Libft..."
				@make -sC $(LIBFT_DIR)

$(NAME):		$(OBJ)
				@echo "Compiling Minishell..."
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS) $(LINKS)
				@echo "\n------------------------------------------\n"
				@echo "📟 Minishell Ready!\n"
				@echo "------------------------------------------\n"

clean:
				@echo "Removing .o object files..."
				@rm -rf $(OBJ_DIR)
				@make clean -C $(LIBFT_DIR)
				@echo "\n------------------------------------------\n"
				@echo "💧 Clean: Removed all the \".o\" files \n"
				@echo "------------------------------------------\n"

fclean:			clean
				@echo "Removing Minishell..."
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@echo "\n------------------------------------------\n"
				@echo "🧼 Fclean: Removed the executables \n"
				@echo "------------------------------------------\n"

re:				fclean all

# Phony targets represent actions not files
.PHONY: all clean fclean re test
