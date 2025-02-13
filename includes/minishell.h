#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <fcntl.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                command table                               */
/* -------------------------------------------------------------------------- */

# define SYNTAX_ERR	2
# define NOT_FOUND	3
# define IS_DIR		4
# define MALLOC_ERR	-1

# define DEBUG 0
# define SHOW_LEXER 0

typedef struct s_command
{
	char	*path;
	char	**args; // args[0] = cmd name (ex: ls)
	size_t	n_args;

	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	size_t		n_commands;

	char		**env;
}	t_command_table;

// pipex.c
char	**get_paths(char **env);

// executor
char	*get_cmd_path(char **paths, t_command cmd);
void	setup_redirection(t_command cmd);

// pipeline.c
int		run_pipeline(t_command_table *table);
void	cleanup_table(t_command_table *table);

// redirect.c
void	redir(t_command *cmd, char *cmd_str, int is_last);

// init.c
int		init_table(char *line, t_command_table *table, int last_cmd);

// ft_split_1space.c
char	**ft_split_1space(const char *s, char c);
void	*free_all(char **res);

// utils.c
int		is_builtin(char *name);
size_t	get_biggest_len(const char *s1, const char *s2);
char	*find_env_var(char **env, const char *to_find, int *index);
int		replace_env_var(char **env, char *to_find, const char *replace);

// checker_utils.c
int		check_needed(char **cmd, const char c_operator);
void	cleanup_arr(void **arr);
int		in_base(const char c, const char *base);
int		token_error(char c1, char c2);

// checker.c
int		check_cmd_line( const char *process_line );

// lexer.c
char	*process_line(const char *cmd_line, char **env, int *code);

// quotes_processing.c
t_list	*process_quotes(const char *line);

// var_processing.c
t_list	*process_expanded_vars(const t_list *lst, char **env);

// syntax_checker.c
int		check_syntax(const char *cmd_line);

// path_checker.c
int		check_cmd_path(const char *cmd);
int		check_dir_validity(const char *path);

/* ------------------------------ built-in cmd ------------------------------ */
// echo.c
int		echo(char **args, int n);

// env.c
int		env(t_command_table table);
char	**duplicate_env(char **old_env);
size_t	arrlen(void **arr);

// pwd.c
int		pwd(char **env);

// export.c
int		export_cmd(t_command_table *table, t_command cmd);

// unset.c
int		unset(t_command_table *table, t_command cmd);

// dirs.c
int		cd_command(const t_command_table *table, const t_command cmd);
int		change_directory(const char *path, char **env);

// debug
void	show_cmd(t_command cmd);
void	show_table(t_command_table table);

char	*remove_quotes(const char *line);

#endif
