#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <fcntl.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                command table                               */
/* -------------------------------------------------------------------------- */

# define SYNTAX_ERR	2
# define NOT_FOUND	127
# define IS_DIR		126
# define MALLOC_ERR	-1

# define DEBUG 0
# define SHOW_LEXER 0

typedef struct s_command
{
	char	**args;
	size_t	n_args;
	int		pid;

	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	size_t		n_commands;

	char		**env;
	char		**exp;
}	t_command_table;

extern int	g_signal_received;

/* ------------------------------ builtin ------------------------------ */

// cd.c
int		cd_command(const t_command_table *table, const t_command cmd);
char	*find_env_var(char **env, char *to_find, int *index);

// echo.c
int		echo(char **args, int n);

// env.c
int		env(t_command_table table);
char	**duplicate_env(char **old_env);
size_t	arrlen(void **arr);

// export.c
int		export_cmd(t_command_table *table, t_command cmd);
char	**update_env(char *arg, char **env);

// pwd.c
int		pwd(void);
char	*get_pwd(void);

// unset.c
int		unset_cmd(t_command_table *table, t_command cmd);
void	handle_cmd(t_command_table *table, char *arg);

// exit.c
void	exit_shell(t_command_table *table, t_command cmd, int *childs);

/* ------------------------------ checker ------------------------------ */

// checker_utils.c
int		in_base(const char c, const char *base);
int		token_error(char c1, char c2);
void	cleanup_arr(void **arr);

// checker.c
int		check_cmd_line( const char *process_line, char **env );

// path_checker.c
int		check_path(const char *cmd_part, char **env);

// redir_checker.c
int		check_redir_in(const char *cmd_line, int i);
int		new_line_error(const char *str, const char last);
char	*remove_quotes_pair(char *s);

// split_line.c
t_list	*split_line(char *line);

// syntax_checker.c
int		check_syntax(const char *cmd_line);

// token_error.c
int		check_token_error(const char *cmd_line, int i, int max_occ,
			char to_find);

int		check_quotes(const char *cmd_line);

/* ------------------------------ executor ------------------------------ */

// cmd_debug.c
void	show_table(t_command_table table);
void	show_cmd(t_command cmd);

// executor.c
int		run_command(t_command *cmd, const t_command_table *table, int *childs);
void	close_fds(t_command cmd);

// paths.c
char	*get_cmd_path(char **paths, t_command cmd);
int		is_builtin(char *name);
char	**get_paths(char **env);

// pipeline.c
int		run_pipeline(t_command_table *table);

// join_lst.c
char	*join_lst(t_list *lst);

// lexer_utils.c
char	toggle_quote(char c, char quote);
int		is_symbol(char c);

// lexer.c
char	*process_line(const char *cmd_line, char **env, int *code);

// quote_utils.c
size_t	get_str_len(const char *str);

// quotes_processing.c
t_list	*process_quotes(const char *line);
char	*remove_quotes(const char *line);

// var_processing.c
t_list	*process_expanded_vars(const t_list *lst, char **env, int last_code);

/* ------------------------------ lexer ------------------------------ */

// join_lst.c
char	*join_lst(t_list *lst);

// lexer_utils.c
char	toggle_quote(char c, char quote);
int		is_symbol(char c);

// lexer.c
char	*process_line(const char *cmd_line, char **env, int *code);

// quote_utils.c
size_t	get_str_len(const char *str);

// quotes_processing.c
t_list	*process_quotes(const char *line);
char	*remove_quotes(const char *line);

// var_processing.c
t_list	*process_expanded_vars(const t_list *lst, char **env, int last_code);

/* ------------------------------ parser ------------------------------ */

// init.c
int		init_table(char *line, t_command_table *table);

// redir.c
// void	redir(t_command *cmd, char *command);
void	redir(t_command *cmd, char *command, int is_last, int i);

// heredoc.c
// int		heredoc(t_command *cmd, char *deli);

/* ------------------------------ other ------------------------------ */

void	new_prompt(t_command_table *table);
void	init_env(t_command_table *table, char **env);
void	cleanup_table(t_command_table *table);
void	handle_signal(int signal);
int		check_interrupt(void);
void	check_piped_execution(void);
char	*get_folder(void);

#endif
