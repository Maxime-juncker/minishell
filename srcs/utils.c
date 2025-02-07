#include "minishell.h"

char	*ft_strcpy_expect_char(char *s, char c)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != c)
			j++;
	res = malloc(j + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			res[j++] = s[i];
		i++;
	}
	free(s);
	res[i] = 0;
	return (res);
}

size_t	get_biggest_len(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	return (ft_max(len1, len2));
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
	if (ft_strncmp(name, "cd", get_biggest_len(name, "cd")) == 0)
		return (1);
	if (ft_strncmp(name, "heredoc", get_biggest_len(name, "heredoc")) == 0)
		return (1);
	return (0);
}

/// @brief find an env variable
/// @param env the env variable
/// @param to_find var to find
/// @param index index of the found variable -1 if not found
/// @return the variable NULL if not found
char	*find_env_var(char **env, const char *to_find, int *index)
{
	int	i = 0;
	size_t	len = ft_strlen(to_find);

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

int	replace_env_var(char **env, const char *to_find, const char *replace)
{
	int	i = 0;
	size_t	len = ft_strlen(to_find);

	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			char *path = ft_strjoin(ft_strjoin(to_find, "="), ft_strdup(replace));
			env[i] = path;
			return (0);
		}
		i++;
	}
	return (-1);
}
