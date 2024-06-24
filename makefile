# Name
NAME	= minishell

# Compiler and Flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -MMD -MP
CPPFLAGS += -I/opt/homebrew/opt/readline/include
LDFLAGS = $(LIBS) -L/opt/homebrew/opt/readline/lib
LINKS = -lft -lreadline

# Libft
LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a
LIBFT			= $(LIBFT_DIR)$(LIBFT_NAME)

# Includes
INC	=	-I ./includes/header_mig\
		-I ./libft/\

# Source files
SRC_DIR	=	sources/
SRC := $(shell find $(SRC_DIRS) -name *.c)
SRCS	=	$(addprefix $(SRC_DIRC), $(SRC))

# Object files
OBJ_DIR	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))

# Build rules
all:			$(LIBFT) $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(INC)

$(OBJS):		$(OBJ_DIR)

$(OBJ_DIR):
				@mkdir $(OBJ_DIR)

$(LIBFT):
				@echo "Making Libft..."
				@make -sC $(LIBFT_DIR)
				@echo "\nLinking:"
				@$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LINKS)
				@echo "..\n"


$(NAME):		$(OBJS)
				@echo "Compiling Minishell..."
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) $(LIBS)
				@echo "Minishell ready."

clean:
				@echo "Removing .o object files..."
				@rm -rf $(OBJ_DIR)
				@make clean -C $(LIBFT_DIR)

fclean:			clean
				@echo "Removing Minishell..."
				@rm -f $(NAME)
				@rm -f $(LIBFT_DIR)$(LIBFT_NAME)

re:		fclean all

# Phony targets represent actions not files
.PHONY: all clean fclean re
