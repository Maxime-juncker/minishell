#include "minishell.h"
#include <dirent.h>
#include <stdio.h>

static void cleanup_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int in_base(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

//!!!! special case for if <> -> bash: syntax error near unexpected token `newline'
//!!!! ls <> file the file is created but is empty, the fd out of ls is the stdout
static int	check_syntax_old(const char *cmd)
{
	int	n_args;
	int	n_redir;
	int	tmp;
	int occ;
	int	i;

	n_args = 0;
	n_redir = 0;
	tmp = 0;

	i = 0;

	while (cmd[i] && in_base(cmd[i], "><") == -1)
	{
		if (cmd[i] != ' ')
			tmp = 1;
		i++;
	}
	if (tmp == 1) // then a cmd is here
		n_args++;

	// store redirection
	tmp = (int)cmd[i];
	occ = 1;
	i++;
	while (cmd[i] && (in_base(cmd[i], "><") > -1 || cmd[i] == ' '))
	{
		//* error
		if (in_base(cmd[i], "><") > -1 && (cmd[i] != tmp || occ == 2)) // >< or ><> or ><<
		{
			// if (tmp == '<' && cmd[i] == '>')
			// {
			// 	printf("minishell$ syntax error near unexpected token `newline\'\n");
			// 	return (SYNTAX_ERR);
			// }
			printf("minishell$ syntax error near unexpected token `%c", cmd[i]);
			if (in_base(cmd[i + 1], "><") > -1)
				printf("%c", cmd[i + 1]);
			printf("\'\n");
			return (SYNTAX_ERR);
		}
		occ++;
		i++;
	}
	n_redir++;

	while (cmd[i] && in_base(cmd[i], "><") == -1)
	{
		if (cmd[i] != ' ')
			tmp = 1;
		i++;
	}
	if (tmp == 1)
		n_args++;

	if (n_args == n_redir + 1 || n_args == n_redir)
		return (0);
	printf("minishell$ syntax error near unexpected token `newline\'\n");
	return (SYNTAX_ERR);
}

static int	check_cmd_path(const char *cmd_line)
{
	int	i;
	t_command	cmd;

	i = 0;
	while (cmd_line[i] && in_base(cmd_line[i], "><") == -1 && cmd_line[i] != ' ')
	{
		i++;
	}
	cmd.args = malloc(1 * sizeof(char *));
	if (!cmd.args)
		return (MALLOC_ERR);
	cmd.args[0] = malloc(i + 1);
	if (cmd.args[0] == NULL)
		return (MALLOC_ERR);
	cmd_line = ft_strtrim(cmd_line, "\'\"");
	ft_strlcpy(cmd.args[0], cmd_line, i + 1);
	if (get_cmd_path(get_paths(__environ), cmd) == NULL)
	{
		printf("minishell$ %s: command not found\n", cmd.args[0]);
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

	// check that it's only the dir
	if (ft_strchr(paths[0], '/') == NULL)
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

int	check_needed(char **cmd, const char operator)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], operator) != NULL)
			return (1);
		i++;
	}
	return (0);
}

int	is_symbols(const char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	check_error(const char *cmd_line, const int i)
{
	int	j;
	int	nb_spaces;

	j = 0;
	nb_spaces = 0;
	while (cmd_line[i - j] == '|' || cmd_line[i - j] == '<' || cmd_line[i - j] == '>' || cmd_line[i - j] == ' ')
	{
		if (cmd_line[i - j] == ' ')
		{
			nb_spaces++;
			j++;
			continue;
		}
		if (j - nb_spaces == 2 || cmd_line[i - j] != cmd_line[i])
		{
			printf("minishell$ syntax error near unexpected token `%c", cmd_line[i]);
			if (cmd_line[i + 1] == cmd_line[i] && (cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>'))
			{
				printf("%c", cmd_line[i + 1]);
			}
			printf("\'\n");
			return (SYNTAX_ERR);
		}
		j++;
	}
	return (0);
}

int	check_syntax(const char *cmd_line)
{
	int		i;
	char	last;

	i = 0;
	last = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')
			if (check_error(cmd_line, i) == SYNTAX_ERR)
				return (SYNTAX_ERR);
		if (cmd_line[i] != ' ')
			last = cmd_line[i];
		i++;
	}
	if (last == '|' )
	{
		printf("minishell$ syntax error near unexpected token `|\'\n");
		return (SYNTAX_ERR);

	}
	if (last == '>' || last == '<')
	{
		printf("minishell$ syntax error near unexpected token `newline\'\n");
		return (SYNTAX_ERR);
	}
	return (0);
}

int	check_cmd( const char *cmd_line )
{
	char	**cmd;
	int		i;
	int		code;

	//* 0. check syntax
	code = check_syntax(cmd_line);
	if (code == SYNTAX_ERR)
		return (SYNTAX_ERR);

	//* 1. splitting every cmd
	cmd = ft_split(cmd_line, '|');
	if (cmd == NULL)
		return (EXIT_FAILURE);

	//* 3. check if cmd right / is a directory
	// if it's a directory, check if it exists
	// otherwise check is the cmd exists
	if (check_needed(cmd, '/'))
	{
		code = check_dir_validity(cmd[0]);
		if (code != 0)
		{
			cleanup_arr((void **)cmd);
			return (code);
		}
	}
	code = check_cmd_path(cmd_line);
	if (code != 0)
	{
		cleanup_arr((void **)cmd);
		return (code);
	}
	cleanup_arr((void **)cmd);
	return (0);
}
