#include "minishell.h"
#include <dirent.h>


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
	while (lst) //* case: >file ls -la
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

int	check_cmd_validity(const char *cmd_name)
{
	t_command	dummy_cmd;
	char		*path;

	if (create_dummy_cmd(cmd_name, &dummy_cmd) == MALLOC_ERR)
		return (MALLOC_ERR);
	path = get_cmd_path(get_paths(__environ), dummy_cmd); //TODO: change le __environ
	cleanup_arr((void **)dummy_cmd.args);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", cmd_name);
		return (NOT_FOUND);
	}
	free(path);
	return (0);
}

int	check_dir_validity(const char *path)
{
	DIR		*dir;

	dir = opendir(path);
	if (!dir)
	{
		printf("minishell: %s: No such file or directory\n", path);
		return (NOT_FOUND);
	}
	closedir(dir);
	printf("minishell: %s: Is a directory\n", path);
	return (IS_DIR);
}

int	check_path(const char *cmd_part)
{
	t_list		*lst;
	char		*name;
	char		*name_no_quote;

	lst = split_line((char *)cmd_part);

	name = ft_strdup(get_cmd_name(lst));
	ft_lstclear(&lst, free);
	if (name == NULL)
		return (NOT_FOUND);
	name_no_quote = remove_quotes_pair(name);
	free(name);
	if (name_no_quote == NULL)
		return (MALLOC_ERR);
	
	if (ft_strchr(name_no_quote, '/') == NULL)
	{
		return (check_cmd_validity(name_no_quote));
	}
	return (check_dir_validity(name_no_quote));
}


#if OLD

int	check_cmd_path(const char *cmd)
{
	int			i;
	t_command	cmd_tmp;
	char		*path;

	i = 0;
	while (cmd[i] && in_base(cmd[i], "><") == -1 && cmd[i] != ' ')
	{
		i++;
	}
	cmd_tmp.args = malloc(2 * sizeof(char *));
	if (!cmd_tmp.args)
		return (MALLOC_ERR);
	cmd_tmp.args[0] = malloc(i + 1);
	cmd_tmp.args[1] = NULL;
	if (cmd_tmp.args[0] == NULL)
		return (MALLOC_ERR);
	ft_strlcpy(cmd_tmp.args[0], cmd, i + 1);
	path = get_cmd_path(get_paths(__environ), cmd_tmp);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", cmd_tmp.args[0]);
		cleanup_arr((void **)cmd_tmp.args);
		free(path);
		return (NOT_FOUND);
	}
	free(path);
	cleanup_arr((void **)cmd_tmp.args);
	return (0);
}



#endif