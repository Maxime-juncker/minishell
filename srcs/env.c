#include "minishell.h"

/// @brief Print the environment variables
/// @param env The environment variables
int	env(void)
{
	int	i;
	char **env;

	env = __environ;
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
