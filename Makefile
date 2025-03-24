NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES_D) -g3 

MAKEFLAGS += --no-print-directory

# ---------------------------------------------------------------------------- #
#                                  directories                                 #
# ---------------------------------------------------------------------------- #

OBJ_D = obj/
BIN_D = ./
INCLUDES_D = -Iincludes/ -Ilibft/includes/ -I/usr/include/readline/

VPATH = srcs/:srcs/builtin:srcs/executor:srcs/lexer:srcs/parser:srcs/checker:srcs/prompt

# ---------------------------------------------------------------------------- #
#                                  srcs / objs                                 #
# ---------------------------------------------------------------------------- #

SRCS = 		main.c							\
			prompt.c						\
			utils.c							\
			echo.c							\
			cd.c							\
			env.c							\
			export.c						\
			export_utils.c					\
			pwd.c							\
			unset.c							\
			executor.c						\
			pipeline.c						\
			checker.c						\
			redir.c							\
			init.c							\
			lexer.c							\
			checker_utils.c					\
			cmd_debug.c						\
			quotes_processing.c				\
			var_processing.c				\
			var_processing_utils.c			\
			syntax_checker.c				\
			path_checker.c					\
			paths.c							\
			split_line.c					\
			lexer_utils.c					\
			join_lst.c						\
			redir_checker.c					\
			token_error.c					\
			quote_checker.c					\
			exit.c							\
			ft_split_operators.c			\
			ft_split_pipe.c					\
			wildcard_processing.c			\
			and_checker.c					\
			wildcard_expanssion.c			\
			wildcard_patern.c				\
			builtin_cmd.c					\
			parenthesis_checker.c			\
			prompt_line.c					\
			wildcard_utils.c				\
			waiter.c						\
			pipeline_utils.c				\
			pipe_checker.c					\
			formater.c						\
			remove_useless_parentheses.c	\
			count_words_operators.c			\
			heredoc.c						\

# ---------------------------------------------------------------------------- #
#                                 adding prefix                                #
# ---------------------------------------------------------------------------- #

OBJ := $(addprefix $(OBJ_D), $(SRCS:.c=.o))
OBJ_NO_MAIN = $(filter-out $(OBJ_D)main.o, $(OBJ))
OBJ_NO_MAIN = $(filter-out $(OBJ_D)prompt.o, $(OBJ))

# ---------------------------------------------------------------------------- #
#                                    colors                                    #
# ---------------------------------------------------------------------------- #

RESET 			= \033[0m
GRAY			= \033[90m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m
CURSOR_OFF 		= \e[?25l
CURSOR_ON 		= \e[?25h

RM = rm -fr

all: 
	$(MAKE) header
	$(MAKE) libft
	$(MAKE) $(BIN_D)$(NAME)

bonus: all

# ---------------------------------------------------------------------------- #
#                                 creating exec                                #
# ---------------------------------------------------------------------------- #

$(BIN_D)$(NAME): $(OBJ) | $(BIN_D)
	$(CC) $(CFLAGS) $(OBJ) libft/bin/libft.a -o $(BIN_D)$(NAME) -L/usr/lib -lreadline
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)$(RESET)\n\n"

$(BIN)/libminishell.a:
	ar rcs $(BIN_D)libminishell.a $(OBJ_NO_MAIN)


# ---------------------------------------------------------------------------- #
#                                   compiling                                  #
# ---------------------------------------------------------------------------- #

$(OBJ_D)%.o: %.c includes/minishell.h libft/bin/libft.a | $(OBJ_D)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(CURSOR_OFF)$(BLUE)"
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls obj | wc -l)" "$(words $(SRCS))"

	# printf "compiling: $@\t\t[$$(ls obj | wc -l)/$(words $(SRCS))]\n"

# ---------------------------------------------------------------------------- #
#                                   cleaning                                   #
# ---------------------------------------------------------------------------- #

.PHONY: clean
clean:
	printf "$(RED)clean:\t$(NAME)\n\n"
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ_D)
	$(RM) $(LOG_D)
	printf "$(RED)---------------------\n\n$(RESET)"

.PHONY: fclean
fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	printf "$(RED)fclean:\t$(NAME)\n"
	$(MAKE) clean

.PHONY: re
re:
		$(MAKE) fclean
		$(MAKE) all

# ---------------------------------------------------------------------------- #
#                                  miscelanous                                 #
# ---------------------------------------------------------------------------- #

.PHONY: header
header:
	printf "$(YELLOW)\n"
	echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ";
	echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ";
	echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ";
	echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ";
	echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗";
	echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝";
	printf "$(YELLOW)[github]: $(GREEN)https://github.com/Maxime-juncker/Minishell.git$(RESET)\n\n"

.PHONY: libft
libft:
	$(MAKE) -C libft

# .PHONY: test
# test:
# 	$(MAKE) all
# 	$(MAKE) $(BIN)/libminishell.a
# 	$(MAKE) test -C better-libunit/

# .PHONY: leaks
# leaks: all
# 	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=ignore_readline.supp -s ./minishell

# ---------------------------------------------------------------------------- #
#                              create directories                              #
# ---------------------------------------------------------------------------- #
$(OBJ_D):
	mkdir -p $(OBJ_D)

$(LOG_D):
	mkdir -p $(LOG_D)

$(BIN_D):
	mkdir -p $(BIN_D)

.SILENT:
