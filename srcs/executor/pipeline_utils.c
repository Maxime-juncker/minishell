/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:30:51 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 15:34:01 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_command cmd)
{
	if (cmd.fd_out != STDOUT_FILENO && cmd.fd_out != -1)
		close(cmd.fd_out);
	if (cmd.fd_in != STDIN_FILENO && cmd.fd_in != -1)
		close(cmd.fd_in);
}

void	close_all_fds(const t_command_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_commands)
	{
		close_fds(table->commands[i]);
		i++;
	}
}

void	cleanup_child(const t_command_table *table)
{
	close_all_fds(table);
	cleanup_arr((void **)table->env);
	cleanup_table((t_command_table *)table);
}
