#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

static char	*get_absolute_path(const char *new_path)
{
	char	*buff;
	int		cur_size;

	chdir(new_path);
	cur_size = 1;
	buff = malloc(cur_size);
	if (buff == NULL)
		return (NULL);
	while (getcwd(buff, cur_size) == NULL)
	{
		free(buff);
		cur_size++;
		buff = malloc(cur_size);
		if (buff == NULL)
			return (NULL);
	}
	return (buff);
}

int	cd_command(const t_command_table *table, const t_command cmd)
{
	char	*path;

	path = NULL;
	if (cmd.n_args > 1)
		path = cmd.args[1];
	const int code = change_directory(path, table->env);
	return (code);
}

int change_directory(const char *path, char **env)
{
	DIR		*dir;
	char	*abs_path;

	if (path == NULL || ft_strncmp(path, "~", ft_strlen(path)) == 0)
		path = find_env_var(env, "HOME", NULL);

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("can't open dir");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("chdir failed");
		return (1);
	}
	abs_path = get_absolute_path(path);
	if (!abs_path)
		return (MALLOC_ERR);
	replace_env_var(env, "PWD", abs_path);
	closedir(dir);
	free(abs_path);
	return (0);
}
