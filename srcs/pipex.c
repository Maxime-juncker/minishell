#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/*                                example table                               */
/* -------------------------------------------------------------------------- */
/* -------------- command example: ls -l | wc -l > outfile.txt -------------- */
/* -------------------------------------------------------------------------- */
t_command_table	example_table(char **env)
{
	t_command_table table;
	// int			pipefd[2]; // [1] = write || [0] = read
	// int	fd = open("outfile.txt", O_TRUNC | O_CREAT | O_WRONLY, 0777);


	table.n_commands = 2;
	table.commands = malloc(sizeof(t_command) * table.n_commands);

	table.commands[0].args = ft_split("ls -l", ' ');
	table.commands[0].n_args = 2;

	table.commands[0].path = get_cmd_path(get_paths(env), table.commands[0]);
	printf("Path: %s\n", table.commands[0].path);

	pipe(table.pipe);


	table.commands[0].fd_in = STDIN_FILENO;
	table.commands[0].fd_out = table.pipe[1];

/* ----------------------------- writing 2nd cmd ---------------------------- */

	table.commands[1].args = ft_split("wc -l", ' ');
	table.commands[1].n_args = 2;

	table.commands[1].path = get_cmd_path(get_paths(env), table.commands[1]);
	printf("Path: %s\n", table.commands[1].path);

	table.commands[1].fd_in = table.pipe[0];
	table.commands[1].fd_out = STDOUT_FILENO;

	return (table);
}
