#include "minishell.h"

/// @brief Print the environment variables
/// @param env The environment variables
int	env(t_command_table table)
{
	int	i;

	i = 0;
	while (table.env[i] != NULL)
	{
		printf("%s\n", table.env[i]);
		i++;
	}
	return (0);
}
