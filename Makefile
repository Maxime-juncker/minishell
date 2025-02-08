NAME = minishell

CFLAGS = $(INCLUDES_D) -g3 -fPIC
MAKEFLAGS += --no-print-directory

LIB_UNIT = better-libunit/

# ---------------------------------------------------------------------------- #
#                                  directories                                 #
# ---------------------------------------------------------------------------- #
OBJ_D = obj/
SRCS_D = srcs/
BUILTIN_D = builtin/
EXECUTOR_D = executor/
LEXER_D = lexer/
PARSER_D = parser/
BIN_D = bin/
LOG_D = log/
INCLUDES_D = -Iincludes/ -Ilibft/includes/ -I/usr/include/readline/

VPATH = srcs/:srcs/builtin:srcs/executor:srcs/lexer:srcs/parser

# ---------------------------------------------------------------------------- #
#                                  srcs / objs                                 #
# ---------------------------------------------------------------------------- #
SRCS = main.c utils.c

BUILTIN_SRC =	echo.c			\
				cd.c			\
				env.c			\
				export_cmd.c	\
				pwd.c			\
				unset.c			\

EXECUTOR_SRC =	executor.c		\
				pipeline.c		\
				pipex_utils.c	\

LEXER_SRC =	checker.c		\

PARSER_SRC =	init.c		\
				redir.c		\

LIB_SRC =	executor.c pipex_utils.c pipeline.c \
			echo.c env.c pwd.c export_cmd.c init.c utils.c unset.c dirs.c \
			redir.c checker.c	\

OBJ := $(SRCS:.c=.o) $(BUILTIN_SRC:.c=.o) $(EXECUTOR_SRC:.c=.o) $(LEXER_SRC:.c=.o)  $(PARSER_SRC:.c=.o)

LIB_OBJ := utils.o $(SRCS:.c=.o) $(BUILTIN_SRC:.c=.o) $(EXECUTOR_SRC:.c=.o) $(LEXER_SRC:.c=.o)  $(PARSER_SRC:.c=.o)

# ---------------------------------------------------------------------------- #
#                                 adding prefix                                #
# ---------------------------------------------------------------------------- #

OBJ := $(addprefix $(OBJ_D), $(OBJ))
SRCS := $(addprefix $(SRCS_D), $(SRCS))
LIB_OBJ := $(addprefix $(OBJ_D), $(LIB_OBJ))

# ---------------------------------------------------------------------------- #
#                                    colors                                    #
# ---------------------------------------------------------------------------- #

RESET 			= \033[0m
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
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	ar rcs $(BIN_D)libminishell.a $(LIB_OBJ) "libft/bin/libft.a"
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"


$(BIN_D)$(NAME): $(OBJ) | $(BIN_D)
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	$(CC) $(CFLAGS) $(OBJ) libft/bin/libft.a -o $(BIN_D)$(NAME) -L/usr/lib -lreadline
	ar rcs $(BIN_D)libminishell.a $(LIB_OBJ) "libft/bin/libft.a"
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)$(RESET)\n\n"


# ---------------------------------------------------------------------------- #
#                                   compiling                                  #
# ---------------------------------------------------------------------------- #

$(OBJ_D)%.o: %.c includes/minishell.h libft/bin/libft.a | $(OBJ_D)
	$(CC) $(CFLAGS) -c $< -o $@

# %.o: %.c includes/minishell.h libft/bin/libft.a | $(OBJ_D)
# 	printf "$(CURSOR_OFF)$(BLUE)"
# 	printf "compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)]\r"
# 	$(CC) $(CFLAGS) -c $< -o $@

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
