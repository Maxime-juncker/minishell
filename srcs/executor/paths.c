/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/28 08:58:57 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*get_exec_name(char *name)
{
	char	*result;

	result = ft_strrchr(name, '/');
	if (result == NULL)
		result = name;
	else
		result++;
	return (result);
}

char	**get_paths(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
	{
		i++;
	}
	if (!env[i])
		return (NULL);
	tmp = env[i] + 5;
	return (ft_split(tmp, ':'));
}

static char	*get_path(char **paths, t_command cmd)
{
	int			i;
	char		*cmd_path;
	struct stat	st;

	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i] != NULL)
	{
		cmd_path = ft_strjoin("/", cmd.args[0]);
		if (malloc_assert(cmd_path, __FILE__, __LINE__, __FUNCTION__))
			return (cleanup_arr((void **)paths), NULL);
		cmd_path = ft_strjoin_free(paths[i], cmd_path, FREE2);
		if (malloc_assert(cmd_path, __FILE__, __LINE__, __FUNCTION__))
			return (cleanup_arr((void **)paths), NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			cleanup_arr((void **)paths);
			stat(cmd.args[0], &st);
			return (cmd_path);
		}
		free(cmd_path);
	}
	cleanup_arr((void **)paths);
	return (NULL);
}

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

char	*get_cmd_path(char **paths, t_command cmd)
{
	struct stat	st;

	if (cmd.args[0][0] == '\0')
		return (NULL);
	if (is_builtin(cmd.args[0]))
	{
		cleanup_arr((void **)paths);
		return (ft_strdup(cmd.args[0]));
	}
	if (ft_strchr(cmd.args[0], '/') != NULL)
	{
		cleanup_arr((void **)paths);
		if (access(cmd.args[0], F_OK) == 0)
		{
			stat(cmd.args[0], &st);
			if (S_ISDIR(st.st_mode))
				return (NULL);
			return (ft_strdup(cmd.args[0]));
		}
		return (NULL);
	}
	return (get_path(paths, cmd));
}
