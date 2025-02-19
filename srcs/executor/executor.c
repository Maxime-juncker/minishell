#include "minishell.h"

void	close_fds(t_command cmd)
{
	if (cmd.fd_out != STDOUT_FILENO)
		close(cmd.fd_out);
	if (cmd.fd_in != STDIN_FILENO)
		close(cmd.fd_in);
}

char	**get_paths(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
	{
		i++;
	}
	tmp = env[i] + 5;
	return (ft_split(tmp, ':'));
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
		return (pwd(table->env));
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
	size_t  i;
	
	i = cmd->n_args;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	show_cmd(*cmd);
	cmd->args[cmd->n_args] = NULL;
}

int	run_command(t_command cmd, const t_command_table *table, int *childs)
{
	int	pid;
	int	code;

	setup_args(&cmd);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		clean(cmd, table);
		free(childs);
		if (is_builtin(cmd.args[0]) == 1)
		{
			code = run_built_in(cmd, table);
			close_fds(cmd);
			cleanup_arr((void **)table->env);
			cleanup_table((t_command_table *)table);
			exit (code);
		}
		if (execve(get_cmd_path(get_paths(table->env), cmd), \
			cmd.args, table->env) == -1)
			alert("execve failed");
	}
	return (close_fds(cmd), pid);
}
