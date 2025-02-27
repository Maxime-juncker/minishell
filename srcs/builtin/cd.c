

#include "minishell.h"
#include <dirent.h>

char	*find_env_var(char **env, char *to_find, int *index)
{
	int		i;
	size_t	len;
	char	*temp;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			if (index != NULL)
				*index = i;
			temp = remove_spaces(env[i] + len + 1);
			if (!temp)
				return (malloc_assert(ERR), NULL);
			return (temp);
		}
		i++;
	}
	if (index != NULL)
		*index = -1;
	return (NULL);
}

static int	change_directory(char *path)
{
	DIR		*dir;
	char	*abs_path;
	char	buffer[4096];

	dir = opendir(path);
	if (!dir)
		return (free(path), perror("minishell: cd: can't open dir"), 1);
	if (chdir(path) == -1)
		return (closedir(dir), free(path),
			perror("\033[0;31mminishell: cd: chdir failed\033[0m"), 1);
	free(path);
	abs_path = getcwd(buffer, 4096);
	closedir(dir);
	if (!abs_path)
		return (malloc_assert(ERR), MALLOC_ERR);
	return (0);
}

int	cd_command(const t_command_table *table, const t_command cmd)
{
	char	*path;
	int		code;
	int		index;

	if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& table->n_commands > 1)
		return (0);
	index = 0;
	if (cmd.n_args > 2)
	{
		ft_dprintf(2, "%sminishell: cd: too many arguments\n%s", RED, RESET);
		return (1);
	}
	else if (cmd.n_args == 2 && ft_strcmp(cmd.args[1], "~"))
		path = ft_strdup(cmd.args[1]);
	else
		path = find_env_var(table->env, "HOME", &index);
	if (index == -1)
		return (ft_dprintf(2, "%sminishell: cd: HOME not set\n%s",
				RED, RESET), 1);
	else if (!path)
		return (MALLOC_ERR);
	code = change_directory(path);
	return (code);
}
