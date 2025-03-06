MAKEFLAGS += --no-print-directory

NAME = tests.out
CC = g++
CFLAGS = -Wall -Wextra -Werror -g3 -fPIE
INCLUDES =	-I../includes/			\
			-I../../includes/		\
			-I../../libft/includes/	\

VPATH = .:builtin:tests:pipeline:echo:executor

SRCS = 		main.cpp					\
			00_executor.cpp				\
			01_check_path.cpp			\
			02_not_found.cpp			\
			03_null_path.cpp			\
			00_builtin.cpp				\
			01_basic_echo.cpp			\
			02_multiple_echo.cpp		\
			03_no_br_echo.cpp			\
			04_no_br_multiple_echo.cpp	\
			05_env_test.cpp				\
			06_export.cpp				\
			07_unset.cpp				\
			08_pwd_test.cpp				\
			09_cd.cpp					\
			00_commands.cpp				\
			01_create_cmd_basic.cpp		\
			02_create_redir.cpp			\
			03_create_cmd_pipe.cpp		\
			03_basic_ls.cpp				\
			04_multiple_pipes.cpp		\
			05_redir_after_pipe.cpp		\
			06_pipe_after_redir.cpp		\
			07_mutiple_redir.cpp		\
			08_expanded_var.cpp			\
			09_single_quote1.cpp		\
			10_single_quote2.cpp		\
			11_double_quote1.cpp		\
			12_double_quote2.cpp		\
			13_redir_in.cpp				\
			14_redir_in_hard.cpp		\
			15_redir_middle_cmd.cpp		\
			16_only_redir.cpp			\
			00_tests.cpp				\
			01_br.cpp					\
			02_syntax_err.cpp			\
			03_dollars.cpp				\
			00_echo.cpp					\
			01_echo_test.cpp			\


OBJ = $(SRCS:.cpp=.o)

FRAMEWORK_LIB = ../bin/libunit.a
TEST_LIB = ../../bin/libminishell.a ../../libft/bin/libft.a

OBJ_D = obj/
OBJ := $(addprefix $(OBJ_D), $(OBJ))

# colors
RED = 			\033[31m
GRAY =			\033[90m
GREEN = 		\033[32m
YELLOW = 		\033[33m
RESET = 		\033[0m
BLUE = 			\033[34m
CURSOR_OFF =	\e[?25l
CURSOR_ON = 	\e[?25h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FRAMEWORK_LIB) $(TEST_LIB) $(INCLUDES) -o $(NAME) -L/usr/lib -lreadline
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"

$(OBJ_D)%.o: %.cpp $(FRAMEWORK_LIB) ../../bin/libminishell.a | $(OBJ_D)
	printf "$(CURSOR_OFF)$(BLUE)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls obj | wc -l)" "$(words $(SRCS))"


clean:
	printf "$(RED)clean:  objs\n"
	rm -rf $(OBJ_D)

fclean: clean
	printf "$(RED)clean:  tests.out\n"
	rm -f $(NAME)

re: fclean all

test:
	$(MAKE) all
	./$(NAME)

$(OBJ_D):
	mkdir -p $(OBJ_D)

.PHONY: all clean fclean re bonus
.SILENT: