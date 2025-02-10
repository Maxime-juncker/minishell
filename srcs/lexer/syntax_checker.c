#include "minishell.h"

static int	continue_chek(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
}

static int	check_error(const char *cmd_line, const int i)
{
	int	j;
	int	nb_spaces;

	j = 0;
	nb_spaces = 0;
	while (i - j >= 0 && continue_chek(cmd_line[i - j]))
	{
		if (cmd_line[i - j] == ' ')
		{
			nb_spaces++;
			j++;
			continue ;
		}
		if (j - nb_spaces == 2 || cmd_line[i - j] != cmd_line[i])
		{
			if (j - nb_spaces == 1 && cmd_line[i - j] == '<')
			{
				j++;
				continue ;
			}
			return (token_error(cmd_line[i], cmd_line[i + 1]));
		}
		j++;
	}
	return (0);
}

static int	new_line_error(const char *str, const char last)
{
	if (last == '|')
		return (token_error('|', *(str - 2)));
	if (last == '>' || last == '<')
	{
		printf("minishell$ syntax error near unexpected token `newline\'\n");
		return (SYNTAX_ERR);
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
		i++;
	if (cmd_line[i] == '|' && cmd_line[i + 1] != '|')
		return (token_error('|', '\0'));
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')
			if (check_error(cmd_line, i) == SYNTAX_ERR)
				return (SYNTAX_ERR);
		if (cmd_line[i] != ' ')
			last = cmd_line[i];
		i++;
	}
	if (new_line_error(cmd_line + i, last) == SYNTAX_ERR)
		return (SYNTAX_ERR);
	return (0);
}
