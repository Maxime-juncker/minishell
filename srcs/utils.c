#include "minishell.h"

size_t	get_biggest_len(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
}

int	is_builtin(char *name)
{
	if (ft_strncmp(name, "echo", get_biggest_len(name, "echo")) == 0)
		return (1);
	if (ft_strncmp(name, "export", get_biggest_len(name, "export")) == 0)
		return (1);
	if (ft_strncmp(name, "unset", get_biggest_len(name, "unset")) == 0)
		return (1);
	if (ft_strncmp(name, "env", get_biggest_len(name, "env")) == 0)
		return (1);

	return (0);
}