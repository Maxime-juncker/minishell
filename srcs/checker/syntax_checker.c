#include "minishell.h"

int	new_line_error(const char *str, const char last)
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

static int	check_error(const char *cmd_line, int i)
{
	char	to_find;
	int		code;

	to_find = cmd_line[i];
	if (to_find == '>')
	{
		code = check_token_error(cmd_line, i, 2, '>');
		if (code != 0)
			return (code);
		return (check_redir_out(cmd_line, i));
	}
	if (to_find == '<')
	{
		code = check_token_error(cmd_line, i, 2, '<');
		if (code != 0)
			return (code);
		return (check_redir_in(cmd_line, i));
	}
	if (to_find == '|')
		return (check_token_error(cmd_line, i, 2, '|'));
	return (0);
}

static int	check_line(const char *cmd_line)
{
	int		i;
	char	last;
	char	quote;
	int		code;

	i = 0;
	last = 0;
	quote = 0;
	while (cmd_line[i])
	{
		quote = toggle_quote(cmd_line[i], quote);
		if (!quote && (cmd_line[i] == '<' || cmd_line[i] == '>'
				|| cmd_line[i] == '|'))
		{
			code = check_error(cmd_line, i);
			if (code != 0)
				return (code);
		}
		if (!quote && cmd_line[i] != ' ')
			last = cmd_line[i];
		i++;
	}
	if (new_line_error(cmd_line + i, last) == SYNTAX_ERR)
		return (SYNTAX_ERR);
	return (0);
}

int	check_syntax(const char *cmd_line)
{
	int		i;

	i = 0;
	while (cmd_line[i] == ' ')
		i++;
	if (cmd_line[i] == '|' && cmd_line[i + 1] != '|')
		return (token_error('|', '\0'));
	return (check_line(cmd_line + i));
}
