#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int	g_signal_received = 0;

static int	wait_for_process(t_command_table *table, int *childs, int code)
{
	int	pid;
	int	i;

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

/// @brief Run every command in the command table
/// @param table The command table to run
/// @return the exit value of the last command
int	run_pipeline(t_command_table *table)
{
	size_t	i;
	int		code;
	int		pid;
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
			if (is_env_cmd(table->commands[i].args[0]))
			{
				show_cmd(table->commands[i]);
				code = run_env_cmd(table, table->commands[i]);
				close_fds(table->commands[i]);
				i++;
				continue ;
			}
			childs[i] = run_command(table->commands[i], table);
		}
		i++;
	}
	return (wait_for_process(table, childs, code));
}
