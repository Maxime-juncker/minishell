#include "minishell.h"

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

size_t	get_arr_size(void **arr)
{
	size_t	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

size_t	get_char_occ(const char *str, const char c)
{
	int		i;
	size_t	occ;

	occ = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			occ++;
		i++;
	}
	return (occ);
}
static int	check_syntax(const char *cmd)
{
	char **tmp;
	size_t	arr_size;
	size_t	occ;

	// check for >
	tmp = ft_split(cmd, '>');
	if (!tmp)
		return (MALLOC_ERR);
	occ = get_char_occ(cmd, '>');
	arr_size = get_arr_size((void**)tmp);
	if (occ != arr_size - 1)
		return (SYNTAX_ERR);

	return (0);
}

int	check_cmd( const char *cmd_line )
{
	char	**cmd;
	int		i;

	//* 1. splitting every cmd
	cmd = ft_split(cmd_line, '|');
	if (cmd == NULL)
		return (EXIT_FAILURE);


	//* 2. checking syntax
	i = 0;
	while (cmd[i])
	{
		if (check_syntax(cmd[i]) == SYNTAX_ERR)
		{
			ft_printf("minishell$ syntax error near\nunexpected token newline\n");
			return (SYNTAX_ERR);
		}
		i++;
	}

	//* 3. check if cmd right / is a directory

	return SYNTAX_ERR;
}
