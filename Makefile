NAME 			= minishell

HEADER			= includes/minishell.h
PATH_READLINE	= /usr/local/include/readline/

OBJ_DIR 		= ./objects
SRC				= $(shell ls ./builtins/*.c) $(shell ls ./signal/*.c) $(shell ls ./executor/*.c) $(shell ls ./src/*.c) $(shell ls ./utils/*.c) $(shell ls ./lexer/*.c) $(shell ls ./parser/*.c) main.c
OBJ				= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CFLAGS 			= -Wall -Wextra -Werror
RM	 			= rm -rf
CC				= cc

all		: $(NAME)

$(NAME)	: $(OBJ) $(HEADER)
			$(CC) -o $@ $(OBJ) -lreadline -L $(PATH_READLINE) -I $(HEADER)

$(OBJ_DIR)/%.o:	%.c	$(HEADER)
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean	:
				$(RM) $(OBJ)

fclean	:		clean
				$(RM) $(NAME) $(OBJ_DIR)

re		:		fclean all

.PHONY	:		all clean fclean re