#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>

void	show_table(t_command_table table);
void	show_cmd(t_command cmd);

/// @brief Run a built-in command
/// @param cmd The command to run
/// @return the exit value of the run command, -1 if the command isn't builtin
int	run_built_in(t_command cmd)
{
	size_t	len;

	len = ft_strlen(cmd.args[0]);
	if (ft_strncmp(cmd.args[0], "echo", len) == 0)
		return (echo(&cmd.args[1], cmd.n_args - 1));
	if (ft_strncmp(cmd.args[0], "env", len) == 0)
		return (env());
	return (-1);
}

/// @brief Run every command in the command table
/// @param table The command table to run
/// @return the exit value of the last command
int	run_pipeline(t_command_table table)
{
	size_t	i;
	int		code;

	// show_table(table);
	i = 0;
	while (i < table.n_commands)
	{
		code = run_command(table.commands[i]);
		i++;
	}
	return (code);
}

void	setup_redirection(t_command cmd)
{
	dup2(cmd.fd_out, STDOUT_FILENO);
	dup2(cmd.fd_in, STDIN_FILENO);
}

/// @brief run a command
/// @param cmd the command to run
/// @return exit code of the command
int	run_command(t_command cmd)
{
	int	pid;
	int	code;

	cmd.args[cmd.n_args] = NULL;

	// need to happen in separated process
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_redirection(cmd);
		if (cmd.fd_out != STDOUT_FILENO)
			close(cmd.fd_out);
		if (run_built_in(cmd) != -1)
		{
			exit (0);
		}
		show_cmd(cmd);
		if (execve(cmd.path, cmd.args, NULL) == -1)
			alert("execve failed");
	}
	if (cmd.fd_out != STDOUT_FILENO)
		close(cmd.fd_out);
	if (cmd.fd_in != STDIN_FILENO)
		close(cmd.fd_in);
	wait(&code);
	return (code);
}

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

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

void	show_cmd(t_command cmd)
{
	int	i;

	printf("%srunning %s (%zu args)\nargs: ", GRAY, cmd.args[0], cmd.n_args);
	i = 0;
	while (i < cmd.n_args)
	{
		printf("%s ", cmd.args[i]);
		i++;
	}
	printf("\nfd_in(%d)\tfd_out(%d)%s\n", cmd.fd_in, cmd.fd_out, RESET);
}