#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
/* -------------------------------------------------------------------------- */
/*                                example table                               */
/* -------------------------------------------------------------------------- */
// command example: ls -l | wc -l < outfile.txt | sleep 3 < infile


t_command_table	example_table(char **env)
{
	t_command_table table;
	t_command	cmd;
	int			pid;
	int			pipefd[2]; // [1] = write || [0] = read


	table.n_commands = 2;
	table.commands = malloc(sizeof(t_command) * table.n_commands);

	table.commands[0].args = ft_split("ls -l", ' ');
	table.commands[0].n_args = 2;

	table.commands[0].path = get_cmd_path(get_paths(env), table.commands[0]);
	printf("Path: %s\n", cmd.path);

	if (pipe(pipefd) == -1)
		return ;

	table.commands[0].fd_int = STDIN_FILENO;
	table.commands[0].fd_out = pipefd[1];

/* ----------------------------- writing 2nd cmd ---------------------------- */

	table.commands[1].args = ft_split("wc -l", ' ');
	table.commands[1].n_args = 2;

	table.commands[1].path = get_cmd_path(get_paths(env), table.commands[1]);
	printf("Path: %s\n", cmd.path);

	table.commands[1].fd_int = pipefd[0];

	int	fd = open("outfile.txt", O_RDONLY, 0777);
	table.commands[1].fd_out = fd;

}

void pipex(char **args, char **env)
{


	// need to happen in separated process
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		setup_redirection(cmd);
		exec(cmd);
	}
	wait(NULL);
}