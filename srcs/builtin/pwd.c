#include <stddef.h>

char	*find_env_var(char **env, const char *to_find, int *index)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			if (index != NULL)
				*index = i;
			return (env[i] + len + 1);
		}
		i++;
	}
	if (index != NULL)
		*index = -1;
	return (NULL);
}

int	pwd(char **env)
{
	char	*dir;

	dir = find_env_var(env, "PWD", NULL);
	if (dir == NULL)
		return (1);
	printf("%s\n", dir);
	return (0);
}
