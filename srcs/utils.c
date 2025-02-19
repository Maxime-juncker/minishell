#include "minishell.h"
#include <signal.h>

void	handle_signal(int signal)
{
	g_signal_received = signal;
}

void	void_signal(int signal)
{
	(void)signal;
}

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "heredoc") == 0)
		return (1);
	return (0);
}

int	is_env_cmd(char *name)
{
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
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

int	replace_env_var(char **env, char *to_find, const char *replace)
{
	int		i;
	size_t	len;
	char	*path;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			free(env[i]);
			path = ft_strjoin_free(ft_strjoin(to_find, "="), \
			ft_strdup(replace), FREE1 | FREE2);
			env[i] = path;
			return (0);
		}
		i++;
	}
	return (-1);
}

char	*remove_quotes_pair(char *s)
{
	char	*tmp;
	char	quote;
	int		i;

	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	quote = 0;
	i = 0;
	while (*s)
	{
		if (*s == quote)
		{
			quote = 0;
			s++;
			continue ;
		}
		else if (quote == 0 && (*s == '\'' || *s == '\"'))
		{
			quote = *s;
			s++;
			continue ;
		}
		tmp[i] = *s;
		i++;
		s++;
	}
	return (tmp);
}
