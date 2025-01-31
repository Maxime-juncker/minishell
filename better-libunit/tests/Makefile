MAKEFLAGS += --no-print-directory

NAME = tests.out
CC = g++
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES =	-I../includes/ -I../../includes -I../../libft/includes				\

TEST_SRCS = executor/00_executor.cpp			\
			executor/01_check_path.cpp			\
			executor/02_not_found.cpp			\
			executor/03_null_path.cpp			\
			builtin/00_builtin.cpp				\
			builtin/01_basic_echo.cpp			\
			builtin/02_multiple_echo.cpp		\
			builtin/03_no_br_echo.cpp			\
			builtin/04_no_br_multiple_echo.cpp	\
			builtin/05_env_test.cpp				\
			builtin/06_export.cpp				\
			builtin/07_unset.cpp				\
			builtin/08_pwd_test.cpp				\
			commands/00_commands.cpp			\
			commands/01_create_cmd_basic.cpp	\
			commands/02_create_redir.cpp		\
			commands/03_create_cmd_pipe.cpp		\
			commands/03_basic_ls.cpp			\
			commands/04_multiple_pipes.cpp		\
			commands/05_redir_after_pipe.cpp	\
			commands/06_pipe_after_redir.cpp	\
			commands/07_mutiple_redir.cpp		\
			commands/08_expanded_var.cpp		\
			commands/09_single_quote1.cpp		\
			commands/10_single_quote2.cpp		\
			commands/11_double_quote1.cpp		\
			commands/12_double_quote2.cpp		\


TEST_OBJS = $(TEST_SRCS:.cpp=.o)
MAIN_OBJ = main.o

FRAMEWORK_LIB = ../bin/libunit.a
TEST_LIB = ../../bin/libminishell.a ../../libft/bin/libft.a

# colors
RED = 			\033[31m
GREEN = 		\033[32m
YELLOW = 		\033[33m
RESET = 		\033[0m
BLUE = 			\033[34m
CURSOR_OFF =	\e[?25l
CURSOR_ON = 	\e[?25h

all: $(NAME)

$(NAME): $(TEST_OBJS) $(MAIN_OBJ)
	printf "$(BLUE)compiling: [$$(find . -type f -name "*.o" | wc -l)/$(shell find . -type f -name "*.cpp" | wc -l)] [OK]\r\n"
	$(CC) $(CFLAGS) -pie $(MAIN_OBJ) $(TEST_OBJS) $(FRAMEWORK_LIB) $(TEST_LIB) $(INCLUDES) -o $(NAME)
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"

%.o: %.cpp $(FRAMEWORK_LIB)
	printf "$(CURSOR_OFF)$(BLUE)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf "compiling: [$$(find . -type f -name "*.o" | wc -l)/$(shell find . -type f -name "*.cpp" | wc -l)]\r"

clean:
	printf "$(RED)clean:  tests.out\n"
	rm -f $(MAIN_OBJ) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re bonus
.SILENT: