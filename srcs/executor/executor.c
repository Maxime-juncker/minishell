/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:54 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/01 10:58:00 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls && wejgoiw || (cd / && pwd) && pwd

#include "minishell.h"
#include "sys/wait.h"

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

	cleanup_arr((void **)table->exp);
	dup2(cmd->fd_out, STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	free(package.childs);
	ft_lstclear(&package.args, cleanup_pacakge);
	if (is_builtin(cmd->args[0]) == 1)
	{
		code = run_built_in(*cmd, table);
		close_all_fds(table);
		cleanup_arr((void **)table->env);
		cleanup_table((t_command_table *)table);
		exit(code);
	}
	close_all_fds(table);
	if (execve(get_cmd_path(get_paths(table->env), *cmd), \
		cmd->args, table->env) == -1)
		alert("execve failed");
}

int	run_command(t_command *cmd, const t_command_table *table,
		t_free_pkg package, int *code)
{
	int	pid;

	*code = check_path(cmd->args[0], table->env);
	if (*code != 0)
		return (close_fds(*cmd), -1);
	setup_args(cmd);
	pid = fork();
	if (pid == -1)
		return (perror("\033[0;31mfork failed"), -1);
	if (pid == 0)
	{
		handle_child_process(cmd, table, package);
	}
	else
	{
		cmd->pid = pid;
		close_fds(*cmd);
	}
	return (pid);
}
