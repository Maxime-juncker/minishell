NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES_D) -g3 -fPIC

MAKEFLAGS += --no-print-directory

# ---------------------------------------------------------------------------- #
#                                  directories                                 #
# ---------------------------------------------------------------------------- #

OBJ_D = obj/
BIN_D = bin/
INCLUDES_D = -Iincludes/ -Ilibft/includes/ -I/usr/include/readline/

VPATH = srcs/:srcs/builtin:srcs/executor:srcs/lexer:srcs/parser:srcs/checker

# ---------------------------------------------------------------------------- #
#                                  srcs / objs                                 #
# ---------------------------------------------------------------------------- #

SRCS = 		main.c						\
			prompt.c					\
			utils.c						\
			echo.c						\
			cd.c						\
			env.c						\
			export.c					\
			export_utils.c				\
			pwd.c						\
			unset.c						\
			executor.c					\
			pipeline.c					\
			checker.c					\
			heredoc.c					\
			redir.c						\
			init.c						\
			lexer.c						\
			checker_utils.c				\
			cmd_debug.c					\
			quotes_processing.c			\
			var_processing.c			\
			syntax_checker.c			\
			path_checker.c				\
			paths.c						\
			split_line.c				\
			lexer_utils.c				\
			join_lst.c					\
			quote_utils.c				\
			redir_checker.c				\
			token_error.c				\
			quote_checker.c				\
			exit.c						\
			ft_split_operators.c		\
			ft_split_except_inquote.c	\
			wildcard_processing.c		\
			and_checker.c				\
			wildcard_expanssion.c		\
			wildcard_patern.c			\

# ---------------------------------------------------------------------------- #
#                                 adding prefix                                #
# ---------------------------------------------------------------------------- #

OBJ := $(addprefix $(OBJ_D), $(SRCS:.c=.o))

# ---------------------------------------------------------------------------- #
#                                    colors                                    #
# ---------------------------------------------------------------------------- #

RESET 			= \033[0m
GRAY			=\033[90m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m
CURSOR_OFF 		= \e[?25l
CURSOR_ON 		= \e[?25h

RM = rm -fr

all: header libft $(BIN_D)$(NAME)

de:
	@echo $(SRCS)
	@echo $(OBJ)

# ---------------------------------------------------------------------------- #
#                                     misc                                     #
# ---------------------------------------------------------------------------- #

.PHONY: header
header:
	printf "$(YELLOW)"
	printf "\n---------------------------------------------------------------------\n"
	printf "  __  __ ___ _   _ ___ ____  _   _ _____ _     _      \n";
	printf " |  \/  |_ _| \ | |_ _/ ___|| | | | ____| |   | |     \n";
	printf " | |\/| || ||  \| || |\___ \| |_| |  _| | |   | |     \n";
	printf " | |  | || || |\  || | ___) |  _  | |___| |___| |___  \n";
	printf " |_|  |_|___|_| \_|___|____/|_| |_|_____|_____|_____| \n";
	printf "                                                      ";
	printf "\n---------------------------------------------------------------------\n"

	printf "$(YELLOW)[github]: $(GREEN)https://github.com/Maxime-juncker/Minishell.git\n\n"

.PHONY: libft
libft:
	$(MAKE) -C libft

# ---------------------------------------------------------------------------- #
#                                 creating exec                                #
# ---------------------------------------------------------------------------- #

$(BIN_D)$(NAME): $(OBJ) | $(BIN_D)
	$(CC) $(CFLAGS) $(OBJ) libft/bin/libft.a -o $(BIN_D)$(NAME) -L/usr/lib -lreadline
	ar rcs $(BIN_D)libminishell.a $(LIB_OBJ) "libft/bin/libft.a"
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)$(RESET)\n\n"

# ---------------------------------------------------------------------------- #
#                                   compiling                                  #
# ---------------------------------------------------------------------------- #

$(OBJ_D)%.o: %.c includes/minishell.h libft/bin/libft.a | $(OBJ_D)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(CURSOR_OFF)$(BLUE)"
	printf "$(GRAY)compiling: $(BLUE)%-30s $(GRAY)[%d/%d]\n" "$<" "$$(ls obj | wc -l)" "$(words $(SRCS))"

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
	$(RM) $(BIN_D)
	printf "$(RED)fclean:\t$(NAME)\n"
	$(MAKE) clean

.PHONY: clog
clog:
	$(RM) $(LOG_D)

.PHONY: re
re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: leaks
leaks: all
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s ./bin/minishell

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
