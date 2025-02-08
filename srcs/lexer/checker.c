#include "minishell.h"
#include <dirent.h>
#include <stdio.h>

//!!!! ls <> file the file is created but is empty, the fd out of ls is the stdout

static int	check_cmd_path(const char *cmd)
{
	int	i;
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

static int	check_dir_validity(const char *path)
{
	DIR		*dir;
	char	**paths;

	paths = ft_split(path, ' ');
	if (paths == NULL)
		return (MALLOC_ERR);

	// check that it's only the dir
	if (ft_strchr(paths[0], '/') == NULL && ft_strchr(paths[0], '.') == NULL)
		return (0);

	// open dir
	dir = opendir(paths[0]);
	if (!dir)
	{
		printf("minishell$ %s: No such file or directory\n", paths[0]);
		return (NOT_FOUND);
	}
	printf("minishell$ %s: Is a directory\n", paths[0]);
	return (IS_DIR);
}

static int	check_error(const char *cmd_line, const int i)
{
	int	j;
	int	nb_spaces;

	j = 0;
	nb_spaces = 0;
	while (cmd_line[i - j] == '|' || cmd_line[i - j] == '<' || cmd_line[i - j] == '>' ||
			cmd_line[i - j] == ' ')
	{
		if (cmd_line[i - j] == ' ')
		{
			nb_spaces++;
			j++;
			continue;
		}
		if (j - nb_spaces == 2 || cmd_line[i - j] != cmd_line[i])
		{
			if (j - nb_spaces == 1 && cmd_line[i - j] == '<')
			{
				j++;
				continue;
			}
			printf("minishell$ syntax error near unexpected token `%c", cmd_line[i]);
			if (cmd_line[i + 1] == cmd_line[i])
				printf("%c", cmd_line[i + 1]);

			printf("\'\n");
			return (SYNTAX_ERR);
		}
		j++;
	}
	return (0);
}

static int	check_syntax(const char *cmd_line)
{
	int		i;
	char	last;

	i = 0;
	last = 0;
	while (cmd_line[i] == ' ')
	{
		i++;
	}
	if (cmd_line[i] == '|' && cmd_line[i + 1] != '|')
	{
		printf("minishell$ syntax error near unexpected token `|\'\n");
		return (SYNTAX_ERR);
	}
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')
			if (check_error(cmd_line, i) == SYNTAX_ERR)
				return (SYNTAX_ERR);
		if (cmd_line[i] != ' ')
			last = cmd_line[i];
		i++;
	}
	if (last == '|')
	{
		printf("minishell$ syntax error near unexpected token `|");
		if (cmd_line[i - 2] == '|')
			printf("%c", cmd_line[i - 2]);
		printf("\'\n");
		return (SYNTAX_ERR);

	}
	if (last == '>' || last == '<')
	{
		printf("minishell$ syntax error near unexpected token `newline\'\n");
		return (SYNTAX_ERR);
	}
	return (0);
}

int	check_cmd( const char *process_line )
{
	char	**cmd;
	int		code;

	//* 0. check syntax
	code = check_syntax(process_line);
	if (code == SYNTAX_ERR)
		return (SYNTAX_ERR);

	//* 1. splitting every cmd
	cmd = ft_split(process_line, '|');
	if (cmd == NULL)
		return (EXIT_FAILURE);
	int	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_strtrim(cmd[i], " ");
		if (!cmd[i]) // ! clean already allocated mem
			return (MALLOC_ERR);
		i++;
	}
	//* 3. check if cmd right / is a directory
	// if it's a directory, check if it exists
	// otherwise check is the cmd exists
	if (check_needed(cmd, '/') || check_needed(cmd, '.'))
	{
		code = check_dir_validity(cmd[0]);
		if (code != 0)
		{
			cleanup_arr((void **)cmd);
			return (code);
		}
	}
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
	cleanup_arr((void **)cmd);
	return (0);
}
