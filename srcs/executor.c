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

char*	get_cmd_path(char** paths, t_command cmd)
{
	int	i = 0;
	char* cmd_path;

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
	ft_putstr_fd("\033[31mCommand not found\n", 2);
	return (NULL);
}

void	exec(t_command cmd)
{
	execve(cmd.path, cmd.args, NULL);
}