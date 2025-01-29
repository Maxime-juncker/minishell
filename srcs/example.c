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

	int	pipefd[2]; // 1 = write | 0 = read
	pipe(pipefd);


	table.n_commands = 3;
	table.commands = malloc(sizeof(t_command) * table.n_commands);

	table.commands[0].args = ft_split("ls -l", ' ');
	table.commands[0].n_args = 2;

	table.commands[0].path = get_cmd_path(get_paths(env), table.commands[0]);
	printf("Path: %s\n", table.commands[0].path);

	table.commands[0].fd_in = STDIN_FILENO;
	table.commands[0].fd_out = pipefd[1];

/* ----------------------------- writing 2nd cmd ---------------------------- */

	table.commands[1].args = ft_split("wc -l", ' ');
	table.commands[1].n_args = 2;

	table.commands[1].path = get_cmd_path(get_paths(env), table.commands[1]);
	printf("Path: %s\n", table.commands[1].path);

	table.commands[1].fd_in = pipefd[0];
	pipe(pipefd);
	table.commands[1].fd_out = pipefd[1];

/* ----------------------------- writing 3rd cmd ---------------------------- */

	table.commands[2].args = ft_split("wc -l", ' ');
	table.commands[2].n_args = 2;

	table.commands[2].path = get_cmd_path(get_paths(env), table.commands[2]);
	printf("Path: %s\n", table.commands[1].path);

	table.commands[2].fd_in = pipefd[0];
	table.commands[2].fd_out = STDOUT_FILENO;

	return (table);
}
