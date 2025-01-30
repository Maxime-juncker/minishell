#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"

# include <fcntl.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                command table                               */
/* -------------------------------------------------------------------------- */

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
char			**get_paths(char **env);
t_command_table	example_table(char **env);

// executor
char			*get_cmd_path(char **paths, t_command cmd);
void			setup_redirection(t_command cmd);

// pipeline.c
int				run_pipeline(t_command_table *table);
int				run_command(t_command cmd, t_command_table *table);

// init.c
int	init_table(char *line, char **env, t_command_table *table);
char	*expand_env_var(const char *str, char **env);

// utils.c
int	is_builtin(char *name);

/* ------------------------------ built-in cmd ------------------------------ */
// echo.c
int		echo(char **args, int n);

// env.c
int		env(t_command_table table);

// pwd.c
int		pwd( void );

// export.c
int		export_cmd(t_command_table *table, t_command cmd);

#endif
