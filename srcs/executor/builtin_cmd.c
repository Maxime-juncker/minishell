/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:03:48 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/10 12:05:07 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_env_cmd(t_command_table *table, t_command cmd,
				t_free_pkg package)
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
		return (exit_shell(table, cmd, package));
	}
	return (0);
}

int	env_stage(t_command_table *table, t_command cmd, int *code,
	t_free_pkg package)
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

int	run_built_in(const t_command cmd, const t_command_table *table)
{
	size_t	len;

	len = ft_strlen(cmd.args[0]);
	if (ft_strncmp(cmd.args[0], "echo", len) == 0)
		return (echo(&cmd.args[1], cmd.n_args - 1));
	if (ft_strncmp(cmd.args[0], "env", len) == 0)
		return (env(*table, cmd));
	if (ft_strncmp(cmd.args[0], "pwd", len) == 0)
		return (pwd());
	return (-1);
}
