/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/17 10:12:41 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	create_dummy_path_cmd(const char *name, t_command *cmd)
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
	ft_dprintf(2, "\033[0;31mminishell: %s: Is a directory\n\033[0m", path);
	return (IS_DIR);
}

static int	check_perm(char *path)
{
	if (!is_builtin(path) && access(path, X_OK) != 0)
	{
		ft_dprintf(2, "%sminishell: %s: Permission denied%s\n",
			RED, path, RESET);
		free(path);
		return (PERM_DENIED);
	}
	free(path);
	return (0);
}

int	check_path(const char *cmd_name, char **env)
{
	t_command	dummy_cmd;
	char		*path;

	if (create_dummy_path_cmd(cmd_name, &dummy_cmd) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (dummy_cmd.args[0][0] == '.' && dummy_cmd.args[0][1] == '\0')
	{
		cleanup_arr((void **)dummy_cmd.args);
		ft_dprintf(2, "%sminishell: .: filename argument required\n", ORANGE);
		ft_dprintf(2, ".: usage: . filename [arguments]%s\n", RESET);
		return (2);
	}
	path = get_cmd_path(get_paths(env), dummy_cmd);
	if (path == NULL && !is_builtin((char *)cmd_name))
	{
		if (ft_strchr(cmd_name, '/') != NULL)
			return (check_dir_validity(cmd_name, dummy_cmd));
		else
			ft_dprintf(2, "%sminishell: %s: command not found\n%s",
				RED, cmd_name, RESET);
		cleanup_arr((void **)dummy_cmd.args);
		return (NOT_FOUND);
	}
	cleanup_arr((void **)dummy_cmd.args);
	return (check_perm(path));
}
