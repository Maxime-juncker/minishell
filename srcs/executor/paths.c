#include "minishell.h"

static void	cleanup(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	relative_path(char *path)
{
	if (path[0] == '.')
		return (1);
	return (0);
}

static char	*get_path(char **paths, t_command cmd)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (paths[++i] != NULL)
	{
		cmd_path = ft_strjoin("/", cmd.args[0]);
		if (cmd_path == NULL)
			return (cleanup(paths), NULL);
		cmd_path = ft_strjoin_free(paths[i], cmd_path, FREE2);
		if (cmd_path == NULL)
			return (cleanup(paths), NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			cleanup(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	cleanup(paths);
	return (NULL);
}

/// @brief return the full path of a command if it exists
/// @param paths the env paths variable
/// @param cmd the command to search
/// @return the full path of the command if it exists, NULL otherwise
char	*get_cmd_path(char **paths, t_command cmd)
{
	int		i;
	char	*cmd_path;

	if (paths == NULL)
		return (NULL);
	if (is_builtin(cmd.args[0]))
	{
		cleanup_arr((void **)paths);
		return (ft_strdup(cmd.args[0]));
	}
	if (relative_path(cmd.args[0]))
	{
		cleanup_arr((void **)paths);
		if (access(cmd.args[0], F_OK) == 0)
			return (ft_strdup(cmd.args[0]));
		return (NULL);
	}
	return (get_path(paths, cmd));
}
