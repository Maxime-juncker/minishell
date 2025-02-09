#include "minishell.h"
#include <stdio.h>

static int	check_dir(char	**cmd)
{
	int	code;

	if (check_needed(cmd, '/') || check_needed(cmd, '.'))
	{
		code = check_dir_validity(cmd[0]);
		if (code != 0)
		{
			cleanup_arr((void **)cmd);
			return (code);
		}
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
		{
			cleanup_arr((void **)cmd);
			return (code);
		}
		i++;
	}
	return (0);
}

char	**split_cmd(const char *process_line)
{
	char	**cmd;
	int		i;

	cmd = ft_split(process_line, '|');
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_strtrim(cmd[i], " ");
		if (!cmd[i])
		{
			cleanup_arr((void **)cmd);
			return (NULL);
		}
		i++;
	}
	return (cmd);
}

int	check_cmd_line( const char *process_line )
{
	char	**cmd;
	int		code;
	int		i;

	code = check_syntax(process_line);
	if (code == SYNTAX_ERR)
		return (SYNTAX_ERR);
	cmd = split_cmd(process_line);
	code = check_dir(cmd);
	if (code != 0)
		return (code);
	code = check_command(cmd);
	if (code != 0)
		return (code);
	cleanup_arr((void **)cmd);
	return (0);
}
