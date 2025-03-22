/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:16:19 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/20 16:18:07 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <unistd.h>

char	*remove_spaces(char *str)
{
	char	*buff;
	char	*new_str;
	int		i;
	char	last;

	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (malloc_assert(buff, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	i = 0;
	last = 0;
	while (*str)
	{
		if (is_whitespace(*str) && is_whitespace(last))
		{
			last = *str;
			str++;
			continue ;
		}
		buff[i] = *str;
		last = *str;
		i++;
		str++;
	}
	new_str = ft_strdup(buff);
	return (free(buff), new_str);
}

static int	change_directory(char *path)
{
	DIR		*dir;

	dir = opendir(path);
	if (!dir)
		return (free(path), perror("\033[0;31mminishell: cd"),
			ft_dprintf(2, "%s", RESET), 1);
	if (chdir(path) == -1)
	{
		closedir(dir);
		free(path);
		perror("\033[0;31mminishell: cd: chdir failed\033[0m");
		return (1);
	}
	closedir(dir);
	free(path);
	return (0);
}

void	update_oldpwd(t_command_table *table)
{
	char		*abs_path;
	char		buffer[4096];
	t_command	cmd_fake;

	abs_path = getcwd(buffer, 4096);
	if (!abs_path)
	{
		ft_dprintf(2, "%schdir: error retrieving current directory: %s%s%s\n",
			RED, "getcwd: cannot access parent directories: ",
			"No such file or directory", RESET);
		return ;
	}
	if (create_dummy_cmd(ft_strjoin("export OLDPWD=", abs_path),
			&cmd_fake) == MALLOC_ERR)
		return ;
	export_cmd(table, cmd_fake);
	cleanup_arr((void **)cmd_fake.args);
}

int	get_cd_path(t_command_table *table, const t_command cmd, char **path)
{
	int		index;

	index = 0;
	if (cmd.n_args == 1 || ft_strcmp(cmd.args[1], "~") == 0)
	{
		*path = find_env_var(table->env, "HOME", &index);
		if (index == -1)
			return (free(*path), ft_dprintf(2,
					"%sminishell: cd: HOME not set\n%s", RED, RESET), 1);
	}
	else if (ft_strcmp(cmd.args[1], "-") == 0)
	{
		*path = find_env_var(table->env, "OLDPWD", &index);
		if (index == -1)
			return (free(*path), ft_dprintf(2,
					"%sminishell: cd: OLDPWD not set\n%s", RED, RESET), 1);
	}
	else
		*path = ft_strdup(cmd.args[1]);
	return (0);
}

int	cd_command(t_command_table *table, const t_command cmd)
{
	int		code;
	char	*path;

	if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& table->n_commands > 1)
		return (0);
	if (cmd.n_args > 2)
	{
		ft_dprintf(2, "%sminishell: cd: too many arguments\n%s", RED, RESET);
		return (1);
	}
	if (ft_strcmp(cmd.args[1], "..") == 0)
	{
		path = get_up();
		if (!path)
			path = ft_strdup("..");
	}
	else if (get_cd_path(table, cmd, &path) == 1)
		return (1);
	if (malloc_assert(path, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
	update_oldpwd(table);
	code = change_directory(path);
	return (code);
}
