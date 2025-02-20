#include "minishell.h"

int	check_quotes(const char *cmd_line)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		{
			if (quote == 0)
				quote = cmd_line[i];
			else if (quote == cmd_line[i])
				quote = 0;
		}
		i++;
	}
	if (quote == 0)
		return (0);
	printf("%sminishell: syntax error missing `%c\' quote%s\n", RED, quote, RESET);
	return (SYNTAX_ERR);
}