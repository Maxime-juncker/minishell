#include "minishell.h"

char	*find_env_var(char **env, char *to_find, int *index)
{
	int		i;
	size_t	len;
	char	buffer[1024];

	if (!ft_strcmp(to_find, "PWD"))
	{
		if (!getcwd(buffer, sizeof(buffer)))
		{
			error("Error using getcwd()");
			return (NULL);
		}
		return (ft_strdup(buffer));
	}
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
	char	*path;

	path = find_env_var(env, "PWD", NULL);
	if (!path)
		return (1);
	printf("%s\n", path);
	return (0);
}
