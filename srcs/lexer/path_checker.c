#include "minishell.h"
#include <dirent.h>

int	check_cmd_path(const char *cmd)
{
	int			i;
	t_command	cmd_tmp;

	i = 0;
	while (cmd[i] && in_base(cmd[i], "><") == -1 && cmd[i] != ' ')
	{
		i++;
	}
	cmd_tmp.args = malloc(1 * sizeof(char *));
	if (!cmd_tmp.args)
		return (MALLOC_ERR);
	cmd_tmp.args[0] = malloc(i + 1);
	if (cmd_tmp.args[0] == NULL)
		return (MALLOC_ERR);
	ft_strlcpy(cmd_tmp.args[0], cmd, i + 1);
	if (get_cmd_path(get_paths(__environ), cmd_tmp) == NULL)
	{
		printf("minishell$ %s: command not found\n", cmd_tmp.args[0]);
		return (NOT_FOUND);
	}
	return (0);
}

int	check_dir_validity(const char *path)
{
	DIR		*dir;
	char	**paths;

	paths = ft_split(path, ' ');
	if (paths == NULL)
		return (MALLOC_ERR);
	if (ft_strchr(paths[0], '/') == NULL && ft_strchr(paths[0], '.') == NULL)
		return (0);
	dir = opendir(paths[0]);
	if (!dir)
	{
		printf("minishell$ %s: No such file or directory\n", paths[0]);
		return (NOT_FOUND);
	}
	printf("minishell$ %s: Is a directory\n", paths[0]);
	return (IS_DIR);
}
