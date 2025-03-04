/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:16:19 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/04 12:28:29 by abidolet         ###   ########.fr       */
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
		if (ft_strscmp(env[i], to_find, "=") == 0)
		{
			if (index != NULL)
				*index = i;
			temp = remove_spaces(env[i] + len + 1);
			if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__))
				return (NULL);
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
		return (free(path), perror("\033[0;31mminishell: cd\033[0m"), 1);
	if (chdir(path) == -1)
	{
		closedir(dir);
		free(path);
		perror("\033[0;31mminishell: cd: chdir failed\033[0m");
		return (1);
	}
	closedir(dir);
	free(path);
	abs_path = getcwd(buffer, 4096);
	if (!abs_path)
		ft_dprintf(2, "%schdir: error retrieving current directory: %s%s%s\n",
			RED, "getcwd: cannot access parent directories: ",
			"No such file or directory", RESET);
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
		return (free(path), ft_dprintf(2, "%sminishell: cd: HOME not set\n%s",
				RED, RESET), 1);
	else if (malloc_assert(path, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
	code = change_directory(path);
	return (code);
}
