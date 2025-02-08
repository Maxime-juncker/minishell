#include "minishell.h"

int	check_needed(char **cmd, const char operator)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], operator) != NULL)
			return (1);
		i++;
	}
	return (0);
}

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
