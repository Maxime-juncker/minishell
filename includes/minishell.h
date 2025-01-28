#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft.h"

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
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	size_t		n_commands;
}	t_command_table;

#endif
