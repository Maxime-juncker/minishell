#include "minishell.h"

char	*get_pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
	{
		printf("%spwd: error retrieving current directory: getcwd:%s%s", RED,
		" cannot access parent directories: No such file or directory\n", RESET);
		return (NULL);
	}
	return (ft_strdup(buffer));
}

int	pwd(void)
{
	char	*path;

	path = get_pwd();
	if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}
