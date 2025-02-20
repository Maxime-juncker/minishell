#include "minishell.h"

static int	count_occ_reverse(const char *str, int i)
{
	int	occ;
	int	c;

	occ = 0;
	c = str[i];
	while (i >= 0 && str[i] == c)
	{
		occ++;
		i--;
		while (i >= 0 && str[i] == ' ')
			i--;
	}
	return (occ);
}

int	check_token_error(const char *cmd_line, int i, int max_occ, char to_find)
{
	int	occ;

	occ = count_occ_reverse(cmd_line, i);
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
