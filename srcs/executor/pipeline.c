/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:50 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/03 12:41:21 by mjuncker         ###   ########.fr       */
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
			if (g_signal_received)
			{
				code = g_signal_received + 128;
				while (i < table->n_commands)
					kill(childs[i++], g_signal_received);
				if (seek_cmd(table, table->name) == -1)
				{
					if (g_signal_received == SIGQUIT)
						printf("Quit (core dumped)");
					printf("\n");
				}
			}
			close_all_fds(table);
			return (code);
		}
	}
	close_all_fds(table);
	return (code);
}

static int	setup_pipeline(int **childs, t_command_table *table)
{
	g_signal_received = 0;
	signal(SIGQUIT, handle_signal);
	*childs = ft_calloc(table->n_commands + 2, sizeof(int));
	if (malloc_assert(childs, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	(*childs)[table->n_commands] = -1;
	return (0);
}

int	run_pipeline(t_command_table *table, t_list *args)
{
	size_t	i;
	int		code;
	int		*childs;

	code = 0;
	if (table->commands[0].n_args == 0)
		return (close_all_fds(table), 0);
	if (setup_pipeline(&childs, table) == MALLOC_ERR)
		return (MALLOC_ERR);
	i = 0;
	while (i < table->n_commands)
	{
		if (table->commands[i].n_args != 0)
		{
			code = check_path(table->commands[i].args[0], table->env);
			if (code != 0)
			{
				close_fds(table->commands[i]);
				childs[i] = -1;
				i++;
				continue;
			}
			if (env_stage(table, table->commands[i], &code,
					(t_free_pkg){childs, args}))
			{
				i++;
				continue ;
			}
			childs[i] = run_command(&table->commands[i], table,
					(t_free_pkg){childs, args}, &code);
		}
		i++;
	}
	return (code = wait_for_process(table, childs, code), free(childs), code);
}
