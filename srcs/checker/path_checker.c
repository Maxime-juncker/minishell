#include "minishell.h"
#include <dirent.h>

// < wekweofj

int	create_dummy_cmd(const char *name, t_command *cmd)
{
	cmd->args = malloc(2 * sizeof(char *));
	if (!cmd->args)
		return (MALLOC_ERR);
	cmd->args[0] = ft_strdup(name);
	if (!cmd->args[0])
	{
		free(cmd->args);
		return (MALLOC_ERR);
	}
	cmd->args[1] = NULL;
	return (0);
}

static const char	*get_cmd_name(t_list *lst)
{
	int			i;
	const char	*name;
	const char	*last;

	last = NULL;
	while (lst)
	{
		name = (const char *)lst->content;
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

int	check_cmd_validity(char **cmd_name, char **env)
{
	t_command	dummy_cmd;
	char		*path;

	if (create_dummy_cmd(*cmd_name, &dummy_cmd) == MALLOC_ERR)
		return (MALLOC_ERR);
	path = get_cmd_path(get_paths(env), dummy_cmd);
	if (path == NULL)
	{
		if (relative_path(dummy_cmd.args[0]))
			return (check_dir_validity(cmd_name));
		else
			printf("minishell: %s: command not found\n", *cmd_name);
		cleanup_arr((void **)dummy_cmd.args);
		free(*cmd_name);
		return (NOT_FOUND);
	}
	cleanup_arr((void **)dummy_cmd.args);
	free(*cmd_name);
	free(path);
	return (0);
}

int	check_dir_validity(char **path)
{
	DIR	*dir;

	dir = opendir(*path);
	if (!dir)
	{
		printf("minishell: %s: No such file or directory\n", *path);
		return (NOT_FOUND);
	}
	closedir(dir);
	printf("minishell: %s: Is a directory\n", *path);
	free(*path);
	return (IS_DIR);
}

int	check_path(const char *cmd_part, char **env)
{
	t_list		*lst;
	char		*name;
	char		*name_no_quote;
	const char	*tmp;

	lst = split_line((char *)cmd_part);
	tmp = get_cmd_name(lst);
	if (!tmp)
		return (0);
	name = ft_strdup(tmp);
	ft_lstclear(&lst, free);
	if (name == NULL)
		return (NOT_FOUND);
	name_no_quote = remove_quotes_pair(name);
	free(name);
	if (name_no_quote == NULL)
		return (MALLOC_ERR);
	if (ft_strchr(name_no_quote, '/') == NULL || name_no_quote[0] == '.')
	{
		return (check_cmd_validity(&name_no_quote, env));
	}
	return (check_dir_validity(&name_no_quote));
}
