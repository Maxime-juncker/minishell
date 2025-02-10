#include "minishell.h"

size_t	arrlen(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char **duplicate_env(char **old_env)
{
	char	**new_env;
	int 	i;

	new_env = malloc(sizeof(char *) * (arrlen((void **)old_env) + 1));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (old_env[i] != NULL)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (new_env[i] == NULL)
		{
			cleanup_arr((void **)new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/// @brief Print the environment variables
/// @param table The environment variables
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
