#include "minishell.h"
#include <signal.h>

void	handle_signal(int signal)
{
	g_signal_received = signal;
}

char	*remove_quotes_pair(char *s)
{
	char	*tmp;
	char	quote;
	int		i;

	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	quote = 0;
	i = 0;
	while (*s)
	{
		if (*s == quote)
		{
			quote = 0;
			s++;
			continue ;
		}
		else if (quote == 0 && (*s == '\'' || *s == '\"'))
		{
			quote = *s;
			s++;
			continue ;
		}
		tmp[i] = *s;
		i++;
		s++;
	}
	return (tmp);
}
