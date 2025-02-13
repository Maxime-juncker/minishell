#include "minishell.h"

static int	continue_check(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
}

int	count_occ_reverse(const char *str, const char to_find, int i)
{
	int	occ;

	occ = 0;
	while (i >= 0 && str[i] == to_find)
	{
		occ++;
		i--;
	}
	return (occ);
}

int	check_token_error(const char *cmd_line, int i, int max_occ, char to_find)
{
	int		occ;

	occ = count_occ_reverse(cmd_line, to_find, i);
	if (occ > max_occ)
	{
		printf("minishell: syntax error near unexpected token `");
		occ = 0;
		while (cmd_line[i] == to_find && occ < max_occ)
		{
			printf("%c", to_find);
			i++;
			occ++;
		}
		printf("\'\n");
		return (SYNTAX_ERR);
	}
	return (0);
}

static int	check_error(const char *cmd_line, int i)
{
	char	to_find;

	to_find = cmd_line[i];
	if (to_find == '>')
		return (check_token_error(cmd_line, i, 2, '>'));
	if (to_find == '<')
		return (check_token_error(cmd_line, i, 3, '<'));
	if (to_find == '|')
		return (check_token_error(cmd_line, i, 2, '|'));
	return (0);
}

static int	new_line_error(const char *str, const char last)
{
	if (last == '|')
		return (token_error('|', *(str - 2)));
	if (last == '>' || last == '<')
	{
		printf("minishell: syntax error near unexpected token `newline\'\n");
		return (SYNTAX_ERR);
	}
	return (0);
}

int	check_syntax(const char *cmd_line)
{
	int		i;
	char	last;
	char	quote;

	i = 0;
	last = 0;
	quote = 0;
	while (cmd_line[i] == ' ')
		i++;
	if (cmd_line[i] == '|' && cmd_line[i + 1] != '|')
		return (token_error('|', '\0'));
	while (cmd_line[i])
	{
		quote = toggle_quote(cmd_line[i], quote);
		if (!quote && (cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|'))
			if (check_error(cmd_line, i) == SYNTAX_ERR)
				return (SYNTAX_ERR);
		if (!quote && cmd_line[i] != ' ')
			last = cmd_line[i];
		i++;
	}
	if (new_line_error(cmd_line + i, last) == SYNTAX_ERR)
		return (SYNTAX_ERR);
	return (0);
}
