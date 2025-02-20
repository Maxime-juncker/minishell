#include "minishell.h"

void	cleanup_arr(void **arr)
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

int	token_error(char c1, char c2)
{
	printf("\033[0;31mminishell: syntax error near unexpected token `%c", c1);
	if (c1 == c2)
		printf("%c", c2);
	printf("\'\n\033[0m");
	return (SYNTAX_ERR);
}

int	in_base(const char c, const char *base)
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
