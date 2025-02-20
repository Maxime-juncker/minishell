#include "minishell.h"
#include <dirent.h>

static int	replace_env_var(char **env, char *to_find, const char *replace)
{
	int		i;
	size_t	len;
	char	*path;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			free(env[i]);
			path = ft_strjoin_free(ft_strjoin(to_find, "="), \
			ft_strdup(replace), FREE1 | FREE2);
			env[i] = path;
			return (0);
		}
		i++;
	}
	return (-1);
}

static char	*get_absolute_path(void)
{
	char	*buff;
	int		cur_size;

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

int	change_directory(const char *path, char **env)
{
	DIR		*dir;
	char	*abs_path;

	if (getcwd(NULL, 0) == NULL)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
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
	abs_path = get_absolute_path();
	if (!abs_path)
		return (MALLOC_ERR);
	replace_env_var(env, "PWD", abs_path);
	closedir(dir);
	free(abs_path);
	return (0);
}

int	cd_command(const t_command_table *table, const t_command cmd)
{
	char	*path;
	int		code;

	path = NULL;
	if (cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		return (0);
	if (cmd.n_args == 2)
		path = cmd.args[1];
	else if (cmd.n_args > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	code = change_directory(path, table->env);
	return (code);
}
