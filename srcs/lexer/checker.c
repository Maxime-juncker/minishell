#include "minishell.h"

static int	check_dir(char	**cmd)
{
	int	code;

	if (check_needed(cmd, '/'))
	{
		code = check_dir_validity(cmd[0]);
		if (code != 0)
			return (code);
	}
	return (0);
}

static int	check_command(char	**cmd)
{
	int	code;
	int	i;

	i = 0;
	while (cmd[i])
	{
		code = check_cmd_path(cmd[i]);
		if (code != 0)
			return (code);
		i++;
	}
	return (0);
}

char	**split_cmd(const char *process_line)
{
	char	**cmd;
	char	**cmd_trimed;
	int		i;

	cmd = ft_split(process_line, '|');
	if (cmd == NULL)
		return (NULL);
	cmd_trimed = ft_calloc(arrlen((void **)cmd) + 1, sizeof(char *));
	if (cmd_trimed == NULL)
	{
		cleanup_arr((void **)cmd);
		return (NULL);
	}
	i = 0;
	while (cmd[i])
	{
		cmd_trimed[i] = ft_strtrim(cmd[i], " ");
		if (!cmd_trimed[i])
		{
			cleanup_arr((void **)cmd);
			cleanup_arr((void **)cmd_trimed);
			return (NULL);
		}
		i++;
	}
	cleanup_arr((void **)cmd);
	return (cmd_trimed);
}

int	check_cmd_line( const char *process_line )
{
	char	**cmd;
	int		code;

	return (0);

	code = check_syntax(process_line);
	if (code == SYNTAX_ERR)
		return (SYNTAX_ERR);
	cmd = split_cmd(process_line);
	if (cmd == NULL)
		return (MALLOC_ERR);
	code = check_dir(cmd);
	if (code != 0)
	{
		cleanup_arr((void **)cmd);
		return (code);
	}
	code = check_command(cmd);
	if (code != 0)
	{
		cleanup_arr((void **)cmd);
		return (code);
	}
	cleanup_arr((void **)cmd);
	return (0);
}
