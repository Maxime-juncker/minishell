#include "minishell.h"
#include "sys/wait.h"

void	close_fds(t_command cmd)
{
	if (cmd.fd_out != STDOUT_FILENO)
		close(cmd.fd_out);
	if (cmd.fd_in != STDIN_FILENO)
		close(cmd.fd_in);
}

static int	run_built_in(const t_command cmd, const t_command_table *table)
{
	size_t	len;

	len = ft_strlen(cmd.args[0]);
	if (ft_strncmp(cmd.args[0], "echo", len) == 0)
		return (echo(&cmd.args[1], cmd.n_args - 1));
	if (ft_strncmp(cmd.args[0], "env", len) == 0)
		return (env(*table));
	if (ft_strncmp(cmd.args[0], "pwd", len) == 0)
		return (pwd());
	return (-1);
}

static void	clean(t_command cmd, const t_command_table *table)
{
	cleanup_arr((void **)table->exp);
	dup2(cmd.fd_out, STDOUT_FILENO);
	dup2(cmd.fd_in, STDIN_FILENO);
	if (cmd.fd_out != STDOUT_FILENO)
		close(cmd.fd_out);
}

static void	setup_args(t_command *cmd)
{
	size_t	i;

	i = cmd->n_args;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	show_cmd(*cmd);
	cmd->args[cmd->n_args] = NULL;
}


void	close_all_fd(const t_command_table *table)
{
	size_t i = 0;

	while (i < table->n_commands)
	{
		close_fds(table->commands[i]);
		i++;
	}
}

int	run_command(t_command *cmd, const t_command_table *table, int *childs, int i)
{
	int	pid;
	int	code;

	setup_args(cmd);

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		clean(*cmd, table);
		free(childs);
		if (is_builtin(cmd->args[0]) == 1)
		{
			code = run_built_in(*cmd, table);
			cleanup_arr((void **)table->env);
			cleanup_table((t_command_table *)table);
			exit (code);
		}
		(void)i;
		close_all_fd(table);
		if (execve(get_cmd_path(get_paths(table->env), *cmd), \
			cmd->args, table->env) == -1)
			alert("execve failed");
	}
	else
	{
		cmd->pid = pid;
		if (cmd->args[0][0] == '.')
		{
			int status;
			waitpid(pid, &status, WUNTRACED);
		}
		close_fds(*cmd);
	}
	return (pid);
}
