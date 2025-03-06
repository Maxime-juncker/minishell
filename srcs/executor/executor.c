/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:54 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 15:33:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls && wejgoiw || (cd / && pwd) && pwd

#include "minishell.h"

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

static void	handle_child_process(t_command *cmd, const t_command_table *table,
	t_free_pkg package)
{
	int		code;

	dup2(cmd->fd_out, STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	free(package.childs);
	cleanup_arr((void **)table->exp);
	ft_lstclear(&package.args, cleanup_pacakge);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		cleanup_child(table);
		exit(1);
	}
	if (is_builtin(cmd->args[0]) == 1)
	{
		code = run_built_in(*cmd, table);
		cleanup_child(table);
		exit(code);
	}
	close_all_fds(table);
	if (execve(get_cmd_path(get_paths(table->env), *cmd), \
		cmd->args, table->env) == -1)
		alert("execve failed");
}

int	run_command(t_command *cmd, const t_command_table *table,
	t_free_pkg package)
{
	int	pid;

	setup_args(cmd);
	pid = fork();
	if (pid == -1)
		return (perror("\033[0;31mfork failed"), -1);
	if (pid == 0)
	{
		if (table->setup_fd != -1)
			close(table->setup_fd);
		handle_child_process(cmd, table, package);
	}
	else
	{
		cmd->pid = pid;
		close_fds(*cmd);
	}
	return (pid);
}
