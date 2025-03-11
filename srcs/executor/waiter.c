/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:38:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/10 13:41:19 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>

static int	seek_cmd(t_command_table *table, char *name)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < table->n_commands)
	{
		if (table->commands[i].args[0] != NULL)
		{
			tmp = get_exec_name(table->commands[i].args[0]);
			if (ft_strcmp(tmp, name) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

static void	propagate_sig(size_t i, t_command_table *table, int *childs)
{
	while (i < table->n_commands)
	{
		kill(childs[i++], g_signal_received);
	}
	if (seek_cmd(table, table->name) == -1)
	{
		if (g_signal_received == SIGQUIT)
			ft_printf("%sQuit (core dumped)%s", RED, RESET);
		ft_printf("\n");
	}
}

int	wait_for_process(t_command_table *table, int *childs, int *code)
{
	size_t	i;

	i = 0;
	while (childs[i] != -1)
	{
		wait(code);
		if (WIFEXITED(*code))
			*code = WEXITSTATUS(*code);
		if (g_signal_received)
		{
			*code = g_signal_received + 128;
			
			propagate_sig(i, table, childs);
			return (close_all_fds(table), *code);
		}
		i++;
	}
	return (close_all_fds(table), *code);
}
