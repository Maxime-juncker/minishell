#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int	g_signal_received = 0;

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

int	is_env_cmd(char *name)
{
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	return (0);
}

static int	wait_for_process(t_command_table *table, int *childs, int code)
{
	int	pid;
	size_t	i;

	signal(SIGQUIT, handle_signal);
	g_signal_received = 0;
	while (1)
	{
		pid = wait(&code);
		if (pid == -1)
		{
			if (g_signal_received)
			{
				if (g_signal_received == SIGINT)
					code = 130;
				i = -1;
				while (++i < table->n_commands)
					kill(childs[i], g_signal_received);
				printf("\n");
			}
			return (code);
		}
	}
	return (signal(SIGQUIT, SIG_IGN), code);
}

int	env_stage( t_command_table *table, t_command cmd, int *code)
{
	if (is_env_cmd(cmd.args[0]))
	{
		show_cmd(cmd);
		*code = run_env_cmd(table, cmd);
		close_fds(cmd);
		return (1);
	}
	return (0);
}

/// @brief Run every command in the command table
/// @param table The command table to run
/// @return the exit value of the last command
int	run_pipeline(t_command_table *table)
{
	size_t	i;
	int		code;
	int		*childs;

	childs = ft_calloc(table->n_commands + 1, sizeof(int));
	if (!childs)
		return (MALLOC_ERR);
	childs[table->n_commands] = -1;
	i = 0;
	while (i < table->n_commands)
	{
		if (table->commands[i].n_args != 0)
		{
			if (env_stage(table, table->commands[i], &code))
			{
				i++;
				continue ;
			}
			childs[i] = run_command(table->commands[i], table, childs);
		}
		i++;
	}
	code = wait_for_process(table, childs, code);
	return (free(childs), code);
}
