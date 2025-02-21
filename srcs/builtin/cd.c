/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:07 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*find_env_var(char **env, char *to_find, int *index)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			if (index != NULL)
				*index = i;
			return (env[i] + len + 1);
		}
		i++;
	}
	if (index != NULL)
		*index = -1;
	return (NULL);
}

static int	change_directory(const char *path, char **env)
{
	DIR		*dir;
	char	*abs_path;
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (ft_dprintf(2, "%sminishell: cd: %s: No such file or directory%s",
				RED, path, RESET), 1);
	free(temp);
	if (path == NULL || ft_strncmp(path, "~", ft_strlen(path)) == 0)
		path = find_env_var(env, "HOME", NULL);
	dir = opendir(path);
	if (dir == NULL)
		return (perror("\033[0;31mcan't open dir"), 1);
	if (chdir(path) == -1)
		return (perror("\033[0;31mchdir failed\033[0m"), 1);
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
	if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& table->n_commands > 1)
		return (0);
	if (cmd.n_args == 2)
		path = cmd.args[1];
	else if (cmd.n_args > 2)
	{
		ft_dprintf(2, "\033[0;31mminishell: cd: too many arguments\n\033[0;31m");
		return (1);
	}
	code = change_directory(path, table->env);
	return (code);
}
