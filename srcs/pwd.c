#include "minishell.h"

int	pwd(void)
{
	char	*dir;

	dir = getenv("PWD");
	if (dir == NULL)
		return (1);
	printf("%s\n", dir);
	return (0);
}
