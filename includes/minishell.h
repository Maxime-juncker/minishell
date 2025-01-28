#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"
# include <fcntl.h>

/* -------------------------------------------------------------------------- */
/*                                command table                               */
/* -------------------------------------------------------------------------- */

typedef struct s_cmd
{
	char	**args; // args[0] = cmd name (ex: ls)
	size_t	n_args;
}	t_cmd;

typedef struct s_command
{
	t_cmd	*cmd;
	char	*infile;
	char	*outfile;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	size_t		n_commands;
}	t_command_table;

// pipex.c
void	pipex(char **args, char **env);
void	exec_cmd(char** paths, t_cmd cmd);
char	**get_path(char **env);

#endif
