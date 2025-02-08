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

char	*expand_env_var2(char *str, char **env)
{
	char	*expanded_str;
	int		i;
	char	quote;

	expanded_str = NULL;
	i = 0;
	quote = 0;
	while (str[i] && str[i] != '\"' && str[i] != '\'')
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		if (i && str[i] == '$' && str[i - 1] != '\'')
			break ;
		if (str[i] == '$' && str[i - 1] != '\\' && quote != '\'')
			expanded_str = process_dollar_sign(str, expanded_str, &i, 0);
		else if (str[i] != '\\')
			expanded_str = ft_charjoin(expanded_str, str[i]);
		if (!expanded_str)
			return (NULL);
		i++;
	}
	free(str);
	if (quote)
		expanded_str = ft_strcpy_expect_char(expanded_str, quote);
	return (expanded_str);
}

char *remove_quotes(const char *line)
{
	char	*new_line;
	int		i;
	char	quote_type;

	new_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 1;
	quote_type = line[0];
	if (line[1] == quote_type)
	{
		new_line[0] = '\0';
		return (new_line);
	}
	new_line[0] = quote_type;
	while (line[i])
	{
		new_line[i] = line[i];
		if (line[i] == quote_type)
		{
			i++;
			break;
		}
		i++;
	}
	new_line[i] = '\0';

	return (new_line);
}

t_list	*process_quotes(const char *line)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	t_list	*lst;
	int		line_len;

	i = 0;
	j = 0;
	lst = NULL;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			tmp = remove_quotes(&line[i]);
			if (tmp[0] != '\0')
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(tmp)));
				i += ft_strlen(tmp);
			}
			else
				i += 2; // +2 for opening in closing quote

			free(tmp);
		}
		else
		{
			char buff[1000];
			j = 0;
			while (line[i] && !(line[i] == '\'' || line[i] == '\"'))
			{
				buff[j] = line[i];
				i++;
				j++;
			}
			buff[j] = 0;
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buff)));
		}
	}
	return (lst);
}

char*	process_expanded_vars(t_list *lst)
{
	t_list	*expanded;
	int		i;
	char	*str;
	char	*process_str;
	int		is_str_literal;

	process_str = NULL;

	while (lst)
	{
		i = 0;
		str = ((char*)lst->content);
		if (str[0] == '\'')
		{
			is_str_literal = 1;
			str = ft_strtrim(str, "\'");
		}
		else
		{
			is_str_literal = 0;
			str = ft_strtrim(str, "\"");
		}
		if (!str)
			return (NULL);
		while (str[i])
		{
			if (str[i] == '$' && !is_str_literal)
			{
				const char *expanded_var = expand_env_var2(ft_strdup(&str[i]), __environ);
				process_str = ft_strjoin(process_str, expanded_var);
				i++;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
			}
			else
			{
				process_str = ft_charjoin(process_str, str[i]);
				i++;
			}
		}
		lst = lst->next;
	}
	return (process_str);
}

char *process_line(const char *cmd_line)
{
	t_list	*process_lst;
	char	*process_str;

	process_lst = process_quotes(cmd_line);
	process_str = process_expanded_vars(process_lst);

	return (process_str);
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
