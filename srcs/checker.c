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
//!!!! ' hola""" ' -> cmd not found hola"""
//!!!! " hola''' " -> cmd not found hola'''

//!!!! special case for if <> -> bash: syntax error near unexpected token `newline'
//!!!! ls <> file the file is created but is empty, the fd out of ls is the stdout

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

// $HOME
int	check_error(const char *cmd_line, const int i)
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

int	check_syntax(const char *cmd_line)
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

size_t	get_new_line_length(const char *cmd_line)
{
	size_t	i;
	char *dup;

	i = 0;
	dup = ft_strdup(cmd_line);
	if (!dup)
		return (1);
	while (*dup)
	{
		if (*dup == '$')
		{
			i += ft_strlen(expand_env_var(ft_strdup(dup), __environ, 0));
			while (*dup != ' ' && *dup)
			{
				dup++;
			}
		}
		if (*dup == '\0')
			break;
		i++;
		dup++;
	}
	dup -= ft_strlen(cmd_line);
	free(dup);
	return (i);
}

char	*get_expanded_line(const char *cmd_line)
{
	char	*new_line;
	size_t	size;
	size_t	i;

	i = 0;
	size = get_new_line_length(cmd_line) + 1;
	new_line = ft_calloc(size, sizeof(char));
	if (new_line == NULL)
		return (NULL);
	while (*cmd_line)
	{
		if (*cmd_line == '$')
		{
			new_line = ft_strjoin(new_line, expand_env_var(ft_strdup(cmd_line), __environ, 0));
			i = ft_strlen(new_line);
			if (new_line == NULL)
				return (NULL);
			while (*cmd_line != ' ' && *cmd_line)
			{
				cmd_line++;
			}
		}
		if (*cmd_line == '\0')
			break;
		new_line[i] = *cmd_line;
		i++;
		cmd_line++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char *remove_quotes(const char *line)
{
	char	*new_line;
	int		i;
	char	quote_type;

	new_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	quote_type = line[0];
	line++;
	while (line[i])
	{
		if (line[i] == quote_type)
			break;
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';

	return (new_line);
}

char	*process_quotes(const char *line)
{
	char	*new_line;
	size_t	i;
	size_t	j;
	char	*tmp;

	new_line = ft_calloc(get_new_line_length(line) + 1, sizeof(char));
	if (!new_line)
		return (NULL);

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			tmp = remove_quotes(&line[i]);
			if (tmp[0] != '\0')
			{
				new_line = ft_strjoin(new_line, tmp);
				i += ft_strlen(tmp);
			}
			free(tmp);
			j = ft_strlen(new_line);
			new_line[j] = 0;
			i += 2; // +2 for opening in closing quote
		}
		else
		{
			new_line[j] = line[i];
			j++;
			i++;
			new_line[j] = 0;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}

char *process_line(const char *cmd_line)
{
	char	*process_line;

	// start by expending the env vars
	process_line = get_expanded_line(cmd_line);

	// remove the first set of " or '
	// "'""'"ls -> ''ls

	process_line = process_quotes(process_line);

	return (process_line);

}

int	check_cmd( const char *cmd_line )
{
	char	**cmd;
	int		code;
	char	*new_line;

	new_line = process_line(cmd_line);

	//* 0. check syntax
	code = check_syntax(new_line);
	if (code == SYNTAX_ERR)
		return (SYNTAX_ERR);

	//* 1. splitting every cmd
	cmd = ft_split(new_line, '|');
	if (cmd == NULL)
		return (EXIT_FAILURE);

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
	code = check_cmd_path(new_line);
	if (code != 0)
	{
		cleanup_arr((void **)cmd);
		return (code);
	}
	cleanup_arr((void **)cmd);
	return (0);
}
