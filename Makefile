NAME = minishell

CFLAGS = $(INCLUDES_D) -g3 -fPIC
MAKEFLAGS += --no-print-directory

LIB_UNIT = better-libunit/

# ---------------------------------------------------------------------------- #
#                                  directories                                 #
# ---------------------------------------------------------------------------- #
OBJ_D = obj/
BIN_D = bin/
INCLUDES_D = -Iincludes/ -Ilibft/includes/ -I/usr/include/readline/

VPATH = srcs/:srcs/builtin:srcs/executor:srcs/lexer:srcs/parser

# ---------------------------------------------------------------------------- #
#                                  srcs / objs                                 #
# ---------------------------------------------------------------------------- #
SRCS = 		main.c				\
			utils.c				\
			echo.c				\
			cd.c				\
			env.c				\
			export_cmd.c		\
			pwd.c				\
			unset.c				\
			executor.c			\
			pipeline.c			\
			pipeline_utils.c	\
			checker.c			\
			redir.c				\
			init.c				\
			ft_split_1space.c	\
			lexer.c				\
			checker_utils.c		\
			cmd_debug.c			\
			quotes_processing.c	\
			var_processing.c	\
			syntax_checker.c	\
			path_checker.c		\
			paths.c				\

LIB_SRC = 	utils.c				\
			echo.c				\
			cd.c				\
			env.c				\
			export_cmd.c		\
			pwd.c				\
			unset.c				\
			executor.c			\
			pipeline.c			\
			pipeline_utils.c	\
			checker.c			\
			redir.c				\
			init.c				\
			ft_split_1space.c	\
			lexer.c				\
			checker_utils.c		\
			cmd_debug.c			\
			quotes_processing.c	\
			var_processing.c	\
			syntax_checker.c	\
			path_checker.c		\
			paths.c				\

OBJ := $(SRCS:.c=.o)

LIB_OBJ := $(LIB_SRC:.c=.o)

# ---------------------------------------------------------------------------- #
#                                 adding prefix                                #
# ---------------------------------------------------------------------------- #

OBJ := $(addprefix $(OBJ_D), $(OBJ))
LIB_OBJ := $(addprefix $(OBJ_D), $(LIB_OBJ))

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

all:
	$(MAKE) header
	$(MAKE) libft
	$(MAKE) $(BIN_D)$(NAME)

de:
	@echo $(SRCS)
	@echo $(OBJ)

# ---------------------------------------------------------------------------- #
#                                     misc                                     #
# ---------------------------------------------------------------------------- #
.PHONY: libft
libft:
	$(MAKE) -C libft

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

# ---------------------------------------------------------------------------- #
#                                 creating exec                                #
# ---------------------------------------------------------------------------- #
$(BIN)/libminishell.a:
	printf "$(GREEN)compiling: success [$$(ls obj | wc -l)/$(words $(SRCS))]\n"
	ar rcs $(BIN_D)libminishell.a $(LIB_OBJ) "libft/bin/libft.a"
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"


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
	$(MAKE) clean -C $(LIB_UNIT)
	$(RM) $(OBJ_D)
	$(RM) $(LOG_D)
	printf "$(RED)---------------------\n\n$(RESET)"

.PHONY: fclean
fclean:
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C $(LIB_UNIT)
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

.PHONY: test
test:
	$(MAKE) all
	$(MAKE) test -C better-libunit/
	# $(MAKE) $(BIN)/libminishell.a

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
