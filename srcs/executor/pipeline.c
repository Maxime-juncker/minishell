/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:50 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 12:35:19 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>

int	g_signal_received = 0;

static int	seek_cmd(t_command_table *table, char *name)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < table->n_commands)
	{
		tmp = get_exec_name(table->commands[i].args[0]);
		if (ft_strcmp(tmp, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	wait_for_process(t_command_table *table, int *childs, int code)
{
	int		pid;
	size_t	i;
	i = -1;
	while (childs[++i])
	{
		pid = wait(&code);
		if (pid == -1)
		{
			if (WIFSIGNALED(code) && WTERMSIG(code) == SIGPIPE)
				return (code);
			if (g_signal_received)
			{
				if (g_signal_received == SIGINT)
					code = 130;
				while (i < table->n_commands)
					kill(childs[i++], g_signal_received);
				if (seek_cmd(table, table->name) == -1)
					printf("\n");
			}
			return (code);
		}
	}
	return (signal(SIGQUIT, SIG_IGN), code);
}

static int	run_env_cmd(t_command_table *table, t_command cmd, t_free_package package)
{
	char	*name;

	name = cmd.args[0];
	if (ft_strcmp(name, "export") == 0)
	{
		return (export_cmd(table, cmd));
	}
	if (ft_strcmp(name, "unset") == 0)
	{
		return (unset_cmd(table, cmd));
	}
	if (ft_strcmp(cmd.args[0], "cd") == 0)
	{
		return (cd_command(table, cmd));
	}
	if (ft_strcmp(cmd.args[0], "exit") == 0)
	{
		exit_shell(table, cmd, package);
	}
	return (0);
}

static int	env_stage(t_command_table *table, t_command cmd, int *code,
	t_free_package package)
{
	if (!ft_strcmp(cmd.args[0], "export")
		|| (!ft_strcmp(cmd.args[0], "unset"))
		|| (!ft_strcmp(cmd.args[0], "cd"))
		|| (!ft_strcmp(cmd.args[0], "exit")))
	{
		show_cmd(cmd);
		*code = run_env_cmd(table, cmd, package);
		close_fds(cmd);
		return (1);
	}
	return (0);
}

int	run_pipeline(t_command_table *table, char **args)
{
	size_t	i;
	int		code;
	int		*childs;

	g_signal_received = 0;
	childs = ft_calloc(table->n_commands + 1, sizeof(int));
	if (!childs)
		return (MALLOC_ERR);
	childs[table->n_commands] = -1;
	i = 0;
	while (i < table->n_commands)
	{
		if (table->commands[i].n_args != 0)
		{
			if (env_stage(table, table->commands[i], &code, (t_free_package){childs, args}))
			{
				i++;
				continue ;
			}
			childs[i] = run_command(&table->commands[i], table, (t_free_package){childs, args}, &code);
		}
		i++;
	}
	code = wait_for_process(table, childs, code);
	return (free(childs), code);
}
