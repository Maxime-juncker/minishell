#include "minishell.h"

static int	get_env_len(char **env, char *arg)
{
	int	len;
	int	diff;

	len = 0;
	diff = 0;
	while (env[len])
	{
		if (arg && !ft_strncmp(env[len], arg, ft_strlen(arg)))
			diff++;
		len++;
	}
	if (diff == 0)
		return (-1);
	return (len);
}

static void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static char	**unset(char **env, char *arg, int len)
{
	char	**cpy;
	int		i;

	cpy = malloc((len + 1) * sizeof(char *));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], arg, ft_strlen(arg)))
		{
			cpy[len] = ft_strdup(env[i]);
			if (!cpy[len])
			{
				cleanup_arr((void **)cpy);
				return (NULL);
			}
			len++;
		}
		i++;
	}
	free_env(env);
	cpy[len] = NULL;
	return (cpy);
}

void	handle_cmd(t_command_table *table, char *arg)
{
	int		len;

	len = get_env_len(table->env, arg);
	if (len != -1)
	{
		table->env = unset(table->env, arg, len);
	}
	len = get_env_len(table->exp, arg);
	if (len != -1)
	{
		table->exp = unset(table->exp, arg, len);
	}
}

int	unset_cmd(t_command_table *table, t_command cmd)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		handle_cmd(table, cmd.args[i]);
		if (table->env == NULL || table->exp == NULL)
			return (MALLOC_ERR);
		i++;
	}
	return (0);
}
