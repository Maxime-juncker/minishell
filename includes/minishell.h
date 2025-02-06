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

typedef struct s_command
{
	char	*path;
	char	**args; // args[0] = cmd name (ex: ls)
	size_t	n_args;

	int	fd_in; // NULL = stdin
	int	fd_out; // NULL = stdout
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	size_t		n_commands;

	char **env;
}	t_command_table;

// pipex.c
char	**get_paths(char **env);

// executor
char	*get_cmd_path(char **paths, t_command cmd);
void	setup_redirection(t_command cmd);

// pipeline.c
int		run_pipeline(t_command_table *table);
int		run_command(t_command cmd, const t_command_table *table);

// init.c
int		init_table(char *line, char **env, t_command_table *table, int last_cmd);
char	*expand_env_var(const char *str, char **env, int last_cmd);
char	**ft_split_str(const char *s, char c);

// utils.c
int		is_builtin(char *name);
size_t	get_biggest_len(const char *s1, const char *s2);
char	*find_env_var(char **env, const char *to_find, int *index);
int		replace_env_var(char **env, const char *to_find, const char *replace);

// heredoc.c
int		heredoc(const t_command cmd);

// checker.c
int		check_cmd( const char *cmd_line );

/* ------------------------------ built-in cmd ------------------------------ */
// echo.c
int		echo(char **args, int n);

// env.c
int		env(t_command_table table);

// pwd.c
int		pwd(char **env);

// export.c
int		export_cmd(t_command_table *table, t_command cmd);

// unset.c
int		unset(t_command_table *table, t_command cmd);

// dirs.c
int	cd_command(const t_command_table *table, const t_command cmd);
int change_directory(const char *path, char **env);

// debug
void	show_cmd(t_command cmd);


#endif
