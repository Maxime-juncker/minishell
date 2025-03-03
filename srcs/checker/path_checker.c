/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/03 10:06:50 by abidolet         ###   ########.fr       */
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

static int	check_dir_validity(const char *path, t_command dummy_cmd)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		ft_dprintf(2, "%sminishell: %s: No such file or directory\n%s",
			RED, path, RESET);
		cleanup_arr((void **)dummy_cmd.args);
		return (NOT_FOUND);
	}
	cleanup_arr((void **)dummy_cmd.args);
	closedir(dir);
	ft_dprintf(2, "%sminishell: %s: Is a directory\n", RED, path, RESET);
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
			return (check_dir_validity(cmd_name, dummy_cmd));
		else
			ft_dprintf(2, "minishell: %s: command not found\n",
				RED, cmd_name, RESET);
		cleanup_arr((void **)dummy_cmd.args);
		return (NOT_FOUND);
	}
	cleanup_arr((void **)dummy_cmd.args);
	free(path);
	return (0);
}
