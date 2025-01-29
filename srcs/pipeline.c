#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>
int	run_pipeline(t_command_table table)
{
	size_t	i;

	i = 0;
	while (i < table.n_commands)
	{
		run_command(table.commands[i], table);
		i++;
	}
	close(table.pipe[0]);
	close(table.pipe[1]);
	return (1);
}

void	setup_redirection(t_command cmd)
{
	// ft_printf("%s %d %d\n", cmd.args[0], cmd.fd_out, cmd.fd_in);
	if (cmd.fd_out != -1 && cmd.fd_out != STDOUT_FILENO)
	{
		dup2(cmd.fd_out, STDOUT_FILENO);
		warning("redirecting output");
		// close(cmd.fd_in);
	}
	if (cmd.fd_in != -1 && cmd.fd_in != STDIN_FILENO)
	{
		dup2(cmd.fd_in, STDIN_FILENO);
		warning("redirecting input");
		// close(cmd.fd_out);
	}
}

int	run_command(t_command cmd, t_command_table table)
{
	int	pid;
	int	code;

	// need to happen in separated process
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_redirection(cmd);
		close(table.pipe[0]);
		close(table.pipe[1]);
		if (execve(cmd.path, cmd.args, NULL) == -1)
			alert("execve failed");
	}
	wait(&code);
	// sleep(1);
	return (code);
}