NAME = minishell
CFLAGS = -Wall -Wextra -Werror $(INCLUDES_D)
MAKEFLAGS += --no-print-directory

SRC =	main.c	\
		pipex.c	\
		pipex_utils.c	\

OBJ = $(SRC:.c=.o)

OBJ_D = obj/
SRCS_D = srcs/
BIN_D = bin/
LOG_D = log/
INCLUDES_D = -Iincludes/ -Ilibft/includes/


OBJ := $(addprefix $(OBJ_D), $(OBJ))
SRCS := $(addprefix $(SRCS_D), $(SRCS))

# colors
RESET 			= \033[0m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m
CURSOR_OFF 		= \e[?25l
CURSOR_ON 		= \e[?25h

RM = rm -fr
ARGS = 451 222 117 441 280
R_ARGS=$(shell python3 rand_numbers.py)

all: header libft $(BIN_D)$(NAME)

.PHONY: lib
lib: $(OBJ) $(BIN_D)
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	ar rcs $(BIN_D)$(NAME).a $(OBJ) "libft/bin/libft.a"
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"

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

$(BIN_D)$(NAME): $(OBJ) $(MAIN_OBJ) $(BIN_D)
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	$(CC) $(CFLAGS) -lreadline $(OBJ) libft/bin/libft.a -o $(BIN_D)$(NAME).out
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"

$(OBJ_D)%.o : $(SRCS_D)%.c includes/minishell.h libft/bin/libft.a | $(OBJ_D)
	printf "$(CURSOR_OFF)$(BLUE)"
	printf "compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)]\r"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	printf "$(RED)clean:\t$(NAME)\n\n"
	$(MAKE) clean -C ./libft
	printf "$(RED)---------------------\n\n$(RESET)"
	$(MAKE) clog

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

# Create directories
$(OBJ_D):
	mkdir -p $(OBJ_D)

$(LOG_D):
	mkdir -p $(LOG_D)

$(BIN_D):
	mkdir -p $(BIN_D)

.PHONY: debug
debug: all $(LOG_D)
	echo "$(RESET)"
	./$(BIN_D)$(NAME).out $(ARGS) > $(LOG_D)$(shell date --iso=seconds).log
	cat $(LOG_D)$(shell date --iso=seconds).log
	echo "$(BLUE)[SAVED]: $(LOG_D)$(shell date --iso=seconds).log"

.SILENT: