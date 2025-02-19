#include "minishell.h"

size_t	get_str_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	return (i);
}
