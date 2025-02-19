#include "minishell.h"
#include <sys/stat.h>

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
	if (ft_strcmp(name, "heredoc") == 0)
		return (1);
	return (0);
}

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
	int			i;
	char		*cmd_path;
	struct stat	st;

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
			stat(cmd.args[0], &st);
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
	struct stat	st;

	if (paths == NULL || cmd.args[0][0] == '\0')
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
