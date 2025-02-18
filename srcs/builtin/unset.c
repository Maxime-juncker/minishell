#include "minishell.h"

static int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

char	**unset(char **env, char *arg)
{
	char	**cpy;
	int		i;
	int		len;

	cpy = malloc(get_env_len(env) * sizeof(char *) + 1);
	if (cpy == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], arg, ft_strlen(arg)))
		{
			cpy[len] = ft_strdup(env[i]);
			len++;
		}
		i++;
	}
	cpy[len] = NULL;
	return (cpy);
}

void	unset_cmd(t_command_table *table, t_command cmd)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		table->env = unset(table->env, cmd.args[i]);
		table->exp = unset(table->exp, cmd.args[i]);
		i++;
	}
}
