/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:07 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 08:50:05 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				return (print_malloc_error("cd.c", 30), NULL);
			return (temp);
		}
		i++;
	}
	if (index != NULL)
		*index = -1;
	return (NULL);
}

static int	change_directory(char *path, char **env)
{
	DIR		*dir;
	char	*abs_path;
	char	buffer[4096];
	int		index;

	index = 0;
	if (path == NULL || !ft_strcmp(path, "~"))
	{
		if (path)
			free(path);
		(void)env;
		path = find_env_var(env, "HOME", &index);
	}
	if (index == -1)
		return (ft_dprintf(2, "%sminishell: cd: HOME is not set%s\n",
				RED, RESET), 1);
	else if (!path)
		return (MALLOC_ERR);
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
		return (MALLOC_ERR);
	return (0);
}

int	cd_command(const t_command_table *table, const t_command cmd)
{
	char	*path;
	int		code;

	if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& table->n_commands > 1)
		return (0);
	path = NULL;
	if (cmd.n_args == 2)
	{
		path = ft_strdup(cmd.args[1]);
		if (!path)
			return (MALLOC_ERR);
	}
	else if (cmd.n_args > 2)
	{
		ft_dprintf(2, "%sminishell: cd: too many arguments\n%s", RED, RESET);
		return (1);
	}
	code = change_directory(path, table->env);
	return (code);
}
