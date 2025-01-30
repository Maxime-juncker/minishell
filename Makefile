NAME = minishell

CFLAGS = $(INCLUDES_D) -g3
MAKEFLAGS += --no-print-directory

LIB_UNIT = better-libunit/

# ---------------------------------------------------------------------------- #
#                                  srcs / objs                                 #
# ---------------------------------------------------------------------------- #
SRC =	main.c			\
		init.c	\
		executor.c		\
		pipex_utils.c	\
		pipeline.c		\
		example.c		\
		echo.c			\
		env.c			\

LIB_SRC =	executor.c pipex_utils.c pipeline.c example.c echo.c env.c

OBJ = $(SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

# ---------------------------------------------------------------------------- #
#                                  directories                                 #
# ---------------------------------------------------------------------------- #
OBJ_D = obj/
SRCS_D = srcs/
BIN_D = bin/
LOG_D = log/
INCLUDES_D = -Iincludes/ -Ilibft/includes/

# ---------------------------------------------------------------------------- #
#                                 adding prefix                                #
# ---------------------------------------------------------------------------- #
OBJ := $(addprefix $(OBJ_D), $(OBJ))
SRCS := $(addprefix $(SRCS_D), $(SRCS))
LIB_OBJ := $(addprefix $(OBJ_D), $(LIB_OBJ))
LIB_SRC := $(addprefix $(SRCS_D), $(LIB_SRC))

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

all: header libft $(BIN_D)$(NAME)

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
.PHONY: lib
lib: all
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	ar rcs $(BIN_D)libminishell.a $(LIB_OBJ) "libft/bin/libft.a"
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"


$(BIN_D)$(NAME): $(OBJ) $(BIN_D)
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	$(CC) $(CFLAGS) -lreadline $(OBJ) libft/bin/libft.a -o $(BIN_D)$(NAME).out
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)$(RESET)\n\n"


# ---------------------------------------------------------------------------- #
#                                   compiling                                  #
# ---------------------------------------------------------------------------- #
$(OBJ_D)%.o : $(SRCS_D)%.c includes/minishell.h libft/bin/libft.a | $(OBJ_D)
	printf "$(CURSOR_OFF)$(BLUE)"
	printf "compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)]\r"
	$(CC) $(CFLAGS) -c $< -o $@

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

.PHONY: test
test: lib
	$(MAKE) test -C better-libunit/

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
