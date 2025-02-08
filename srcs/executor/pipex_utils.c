#include "minishell.h"

char	**get_paths(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
	{
		i++;
	}
	tmp = env[i] + 5;
	return (ft_split(tmp, ':'));
}
