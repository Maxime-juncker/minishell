#include "minishell.h"

int	pwd(char **env)
{
	char	*dir;

	dir = find_env_var(env, "PWD", NULL);

	if (dir == NULL)
		return (1);
	printf("%s\n", dir);
	return (0);
}
