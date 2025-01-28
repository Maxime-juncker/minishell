NAME = minishell
CFLAGS = -Wall -Wextra -Werror $(INCLUDES_D)
# CFLAGS = -Wall -Wextra -Werror $(INCLUDES_D) -g3 -D DEBUG=1
MAKEFLAGS += --no-print-directory

SRC =	main.c

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


.PHONY: libft
libft:
	$(MAKE) -C libft

.PHONY: header
header:
	printf "$(YELLOW)"
	printf "\n---------------------------------------------------------------------"
	printf "\n\t ___ _ _  __  _ _         __  _ _ _   _   ___ "
	printf "\n\t| o \\ | |/ _|| U |       / _|| | | | / \\ | o \\"
	printf "\n\t|  _/ U |\\_ \\|   |       \\_ \\| V V || o ||  _/"
	printf "\n\t|_| |___||__/|_n_|  ___  |__/ \\_n_/ |_n_||_|  "
	printf "\n\t                   |___|                      "
	printf "\n\n---------------------------------------------------------------------\n"

	printf "[Author]: $(GREEN)Maxime Juncker"
	printf "$(YELLOW)\t[github]: $(GREEN)https://github.com/Maxime-juncker\n\n"

$(BIN_D)$(NAME): $(OBJ) $(BIN_D)
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls srcs | wc -l)] [OK]\r\n"
	$(CC) $(CFLAGS) $(OBJ) libft/bin/libft.a -o $(BIN_D)$(NAME)
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
	$(BIN_D)./push_swap $(ARGS) > $(LOG_D)$(shell date --iso=seconds).log
	cat $(LOG_D)$(shell date --iso=seconds).log
	echo "$(BLUE)[SAVED]: $(LOG_D)$(shell date --iso=seconds).log"

.PHONY: rdebug
rdebug: all $(LOG_D)
	$(BIN_D)./push_swap $(R_ARGS) > $(LOG_D)$(shell date --iso=seconds).log
	cat $(LOG_D)$(shell date --iso=seconds).log
	echo "$(BLUE)[SAVED]: $(LOG_D)$(shell date --iso=seconds).log"

visu: all
	make -C push_swap_visualizer/build/
	./push_swap_visualizer/build/bin/visualizer

.SILENT: