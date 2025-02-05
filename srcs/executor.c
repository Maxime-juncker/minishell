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

// @brief return the full path of a command if it exist
// @param paths the env paths variable
// @param cmd the command to search
// @return the full path of the command if it exist, NULL otherwise
char*	get_cmd_path(char** paths, t_command cmd)
{
	int	i = 0;
	char* cmd_path;

	if (is_builtin(cmd.args[0]))
		return (ft_strdup(cmd.args[0]));
	while (paths[i] != NULL)
	{
		cmd_path = ft_strjoin("/", cmd.args[0]);
		if (cmd_path == NULL)
			return (NULL);
		cmd_path = ft_strjoin(paths[i], cmd_path);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			cleanup(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	cleanup(paths);
	return (NULL);
}
