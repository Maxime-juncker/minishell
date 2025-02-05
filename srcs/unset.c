#include "minishell.h"

static int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

int	unset(t_command_table *table, const t_command cmd)
{
	char **cpy;
	int		i;
	int		len = 0;

	// cpy env
	cpy = malloc(get_env_len(table->env) * sizeof(char *));
	if (cpy == NULL)
		return (1);
	i = 0;
	while (table->env[i] != NULL)
	{
		if (ft_strncmp(table->env[i], cmd.args[1], ft_strlen(cmd.args[1])) != 0)
		{
			cpy[i] = table->env[i];
			len++;
		}
		i++;
	}
	cpy[len] = NULL;
	table->env = cpy;
	return (0);

}