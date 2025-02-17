#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int g_signal_received = 0;

/// @brief Run a built-in command
/// @param cmd The command to run
/// @param table command table
/// @return the exit value of the run command, -1 if the command isn't builtin
static int	run_built_in(const t_command cmd, const t_command_table *table)
{
	size_t	len;

	len = ft_strlen(cmd.args[0]);
	if (ft_strncmp(cmd.args[0], "echo", len) == 0)
		return (echo(&cmd.args[1], cmd.n_args - 1));
	if (ft_strncmp(cmd.args[0], "env", len) == 0)
		return (env(*table));
	if (ft_strncmp(cmd.args[0], "pwd", len) == 0)
		return (pwd(table->env));
	return (-1);
}

static int	run_env_cmd(t_command_table *table, t_command cmd)
{
	char	*name;

	name = cmd.args[0];
	if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
	{
		export_cmd(table, cmd);
		return (1);
	}
	if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
	{
		unset(table, cmd);
		return (1);
	}
	if (ft_strncmp(cmd.args[0], "cd", ft_strlen(name)) == 0)
	{
		cd_command(table, cmd);
		return (1);
	}
	return (0);
}

/// @brief run a command
/// @param cmd the command to run
/// @param table command table
/// @return child process pid
static int	run_command(t_command cmd, const t_command_table *table)
{
	int	pid;
	int	code;

	show_cmd(cmd);
	cmd.args[cmd.n_args] = NULL;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_redirection(cmd);
		if (cmd.fd_out != STDOUT_FILENO)
			close(cmd.fd_out);
		if (is_builtin(cmd.args[0]) == 1)
		{
			code = run_built_in(cmd, table);
			if (cmd.fd_out != STDOUT_FILENO)
				close(cmd.fd_out);
			if (cmd.fd_in != STDIN_FILENO)
				close(cmd.fd_in);
			cleanup_table((t_command_table *)table);
			exit (code);
		}
		if (execve(get_cmd_path(get_paths(table->env), cmd), cmd.args, table->env) == -1)
			alert("execve failed");
	}
	if (cmd.fd_out != STDOUT_FILENO)
		close(cmd.fd_out);
	if (cmd.fd_in != STDIN_FILENO)
		close(cmd.fd_in);
	return (pid);
}

void	cleanup_table(t_command_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_commands)
	{
		cleanup_arr((void **)table->commands[i].args);
		i++;
	}
	free(table->commands);
}

/// @brief Run every command in the command table
/// @param table The command table to run
/// @return the exit value of the last command
int	run_pipeline(t_command_table *table)
{
	size_t	i;
	int		code;
	int		pid;
	int		*childs;

	childs = ft_calloc(table->n_commands, sizeof(int));
	if (!childs)
		return (MALLOC_ERR);

	i = 0;
	signal(SIGQUIT, handle_signal);
	// signal(SIGINT, void_signal);
	while (i < table->n_commands)
	{
		if (table->commands[i].n_args == 0)
		{
			i++;
			continue ;
		}
		if (run_env_cmd(table, table->commands[i]))
		{
			if (table->commands[i].fd_out != STDOUT_FILENO)
				close(table->commands[i].fd_out);
			if (table->commands[i].fd_in != STDIN_FILENO)
				close(table->commands[i].fd_in);
			i++;
			continue ;
		}
		childs[i] = run_command(table->commands[i], table);
		i++;
	}

	g_signal_received = 0;
	while (1)
	{
		pid = wait(&code);
		if (pid == -1)
		{
			if (g_signal_received) // wait interupted by sign
			{
				i = 0;
				while (i < table->n_commands)
				{
					// if (g_signal_received == SIGQUIT)
					// 	printf("Quit (core dumped)");
					kill(childs[i], g_signal_received);
					i++;
				}
				printf("\n");
			}
			break;
		}
	}
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handle_signal);

	return (code);
}
