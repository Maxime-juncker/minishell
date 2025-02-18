#include "minishell.h"

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

int	run_env_cmd(t_command_table *table, t_command cmd)
{
	char	*name;
	int		i;

	name = cmd.args[0];
	if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
	{
		return (export_cmd(table, cmd));
	}
	if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
	{
		return (unset_cmd(table, cmd));
	}
	if (ft_strncmp(cmd.args[0], "cd", ft_strlen(name)) == 0)
	{
		return (cd_command(table, cmd));
	}
	return (0);
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

void	close_fds(t_command cmd)
{
	if (cmd.fd_out != STDOUT_FILENO)
		close(cmd.fd_out);
	if (cmd.fd_in != STDIN_FILENO)
		close(cmd.fd_in);
}

/// @brief run a command
/// @param cmd the command to run
/// @param table command table
/// @return child process pid
int	run_command(t_command cmd, const t_command_table *table)
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
			close_fds(cmd);
			cleanup_table((t_command_table *)table);
			exit (code);
		}
		if (execve(get_cmd_path(get_paths(table->env), cmd), \
			cmd.args, table->env) == -1)
			alert("execve failed");
	}
	return (close_fds(cmd), pid);
}
