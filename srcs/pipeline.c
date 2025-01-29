#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>

void	show_table(t_command_table table)
{
	int	i = 0;
	while (i < table.n_commands)
	{
		printf("%s%s:\n", GRAY, table.commands[i].args[0]);
		printf("  fd: in (%d) out (%d)\n", table.commands[i].fd_in, table.commands[i].fd_out);
		printf("%s", RESET);
		i++;
	}

}

int	run_pipeline(t_command_table table)
{
	size_t	i;

	// show_table(table);
	i = 0;
	while (i < table.n_commands)
	{
		run_command(table.commands[i], table);
		i++;
	}

	return (1);
}

void	setup_redirection(t_command cmd)
{
	dup2(cmd.fd_out, STDOUT_FILENO);
	dup2(cmd.fd_in, STDIN_FILENO);
}

int	run_command(t_command cmd, t_command_table table)
{
	int	pid;
	int	code;

	// need to happen in separated process
	printf("%sRunning: %s%s\n", GRAY, cmd.args[0], RESET);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_redirection(cmd);
		if (cmd.fd_out != STDOUT_FILENO)
			close(cmd.fd_out);
		if (execve(cmd.path, cmd.args, NULL) == -1)
			alert("execve failed");
	}
	close(cmd.fd_out);
	close(cmd.fd_in);
	wait(NULL);
	return (0);
}