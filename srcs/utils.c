#include "minishell.h"

int	is_builtin(char *name)
{
	if (ft_strncmp(name, "echo", ft_strlen(name)) == 0)
		return (1);
	if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
		return (1);
	if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
		return (1);
	if (ft_strncmp(name, "env", ft_strlen(name)) == 0)
		return (1);

	return (0);
}