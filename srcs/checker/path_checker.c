/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 13:02:57 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	create_dummy_cmd(const char *name, t_command *cmd)
{
	cmd->args = malloc(2 * sizeof(char *));
	if (malloc_assert(cmd->args, INFO))
		return (MALLOC_ERR);
	cmd->args[0] = ft_strdup(name);
	if (malloc_assert(cmd->args[0], INFO))
		return (free(cmd->args), MALLOC_ERR);
	cmd->args[1] = NULL;
	return (0);
}

static char	*get_cmd_name(t_list *lst)
{
	char	*name;
	char	*last;

	last = NULL;
	while (lst)
	{
		name = (char *)lst->content;
		if (in_base(name[0], "><") != -1)
			lst = lst->next;
		else
		{
			if (last && in_base(last[ft_strlen(last) - 1], "><") == -1)
				return (name);
			else if (!last && in_base(name[0], "><") == -1)
				return (name);
			else
				lst = lst->next;
		}
		last = name;
	}
	return (NULL);
}

static int	check_dir_validity(char **path)
{
	DIR	*dir;

	dir = opendir(*path);
	if (!dir)
	{
		ft_dprintf(2, "%sminishell: %s: No such file or directory\n%s",
			RED, *path, RESET);
		return (NOT_FOUND);
	}
	closedir(dir);
	ft_dprintf(2, "\033[0;31mminishell: %s: Is a directory\n\033[0m", *path);
	free(*path);
	return (IS_DIR);
}

static int	check_cmd_validity(char **cmd_name, char **env)
{
	t_command	dummy_cmd;
	char		*path;

	if (create_dummy_cmd(*cmd_name, &dummy_cmd) == MALLOC_ERR)
		return (free(*cmd_name), MALLOC_ERR);
	path = get_cmd_path(get_paths(env), dummy_cmd);
	if (path == NULL && !is_builtin(*cmd_name))
	{
		if (ft_strchr(*cmd_name, '/') != NULL)
			return (check_dir_validity(cmd_name));
		else
			ft_dprintf(2, "\033[0;31mminishell: %s: command not found\n\033[0m",
				*cmd_name);
		cleanup_arr((void **)dummy_cmd.args);
		free(*cmd_name);
		return (NOT_FOUND);
	}
	cleanup_arr((void **)dummy_cmd.args);
	free(*cmd_name);
	free(path);
	return (0);
}

int	check_path(const char *cmd_part, char **env)
{
	t_list		*lst;
	char		*name;
	char		*name_no_quote;

	lst = split_line((char *)cmd_part);
	if (malloc_assert(lst, INFO))
		return (MALLOC_ERR);
	name = ft_strdup(get_cmd_name(lst));
	ft_lstclear(&lst, free);
	if (name == NULL)
		return (NOT_FOUND);
	name_no_quote = remove_quotes_pair(name);
	free(name);
	if (malloc_assert(name_no_quote, INFO))
		return (MALLOC_ERR);
	return (check_cmd_validity(&name_no_quote, env));
}
