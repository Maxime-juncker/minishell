#include "minishell.h"

char	**get_path(char **env)
{
	int	i = 0;

	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
	{
		i++;
	}

	char *tmp = env[i] + 5;
	return (ft_split(tmp, ':'));
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

void	exec_cmd(char** paths, t_cmd cmd)
{
	int	i = 0;
	char* cmd_path;

	while (paths[i] != NULL)
	{
		cmd_path = ft_strjoin("/", cmd.args[0]);
		if (cmd_path == NULL)
			return ;
		cmd_path = ft_strjoin(paths[i], cmd_path);
		if (cmd_path == NULL)
			return ;
		if (access(cmd_path, F_OK) == 0)
		{
			cleanup(paths);
			execve(cmd_path, cmd.args, NULL);
			return ;
		}
		free(cmd_path);
		i++;
	}
	cleanup(paths);
	ft_putstr_fd("\033[31mCommand not found\n", 2);
}

