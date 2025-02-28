/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/28 13:12:22 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	create_dummy_cmd(const char *name, t_command *cmd)
{
	cmd->args = malloc(2 * sizeof(char *));
	if (malloc_assert(cmd->args, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	cmd->args[0] = ft_strdup(name);
	if (malloc_assert(cmd->args[0], __FILE__, __LINE__, __FUNCTION__))
		return (free(cmd->args), MALLOC_ERR);
	cmd->args[1] = NULL;
	return (0);
}

static int	check_dir_validity(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		ft_dprintf(2, "%sminishell: %s: No such file or directory\n%s",
			RED, path, RESET);
		return (NOT_FOUND);
	}
	closedir(dir);
	ft_dprintf(2, "\033[0;31mminishell: %s: Is a directory\n\033[0m", path);
	return (IS_DIR);
}

int	check_path(const char *cmd_name, char **env)
{
	t_command	dummy_cmd;
	char		*path;

	if (create_dummy_cmd(cmd_name, &dummy_cmd) == MALLOC_ERR)
		return (MALLOC_ERR);
	path = get_cmd_path(get_paths(env), dummy_cmd);
	if (path == NULL && !is_builtin((char *)cmd_name))
	{
		if (ft_strchr(cmd_name, '/') != NULL)
			return (check_dir_validity(cmd_name));
		else
			ft_dprintf(2, "\033[0;31mminishell: %s: command not found\n\033[0m",
				cmd_name);
		cleanup_arr((void **)dummy_cmd.args);
		return (NOT_FOUND);
	}
	cleanup_arr((void **)dummy_cmd.args);
	free(path);
	return (0);
}
