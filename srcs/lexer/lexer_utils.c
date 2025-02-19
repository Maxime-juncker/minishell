#include "minishell.h"

char	toggle_quote(char c, char quote)
{
	if (c == '\'' || c == '\"')
	{
		if (quote == c)
			return (0);
		else
			return (c);
	}
	return (quote);
}

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
