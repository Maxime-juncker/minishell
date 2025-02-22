/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:00 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/22 20:49:24 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void	init_env(t_command_table *table, char **env)
{
	table->env = duplicate_env(env);
	if (table->env == NULL)
		exit(EXIT_FAILURE);
	table->exp = duplicate_env(env);
	if (table->exp == NULL)
	{
		cleanup_arr((void **)table->env);
		exit(EXIT_FAILURE);
	}
}

int	check_interrupt(void)
{
	if (g_signal_received)
		rl_done = 1;
	return (0);
}

void	handle_signal(int signal)
{
	g_signal_received = signal;
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
