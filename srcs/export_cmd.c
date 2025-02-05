#include "minishell.h"

static int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}


int	export_cmd(t_command_table *table, t_command cmd)
{
	char **cpy;
	int		i;

	// cpy env
	cpy = malloc((get_env_len(table->env) + 2) * sizeof(char *)); //? +2 because 1 for the new var and 1 for the final null;
	if (cpy == NULL)
		return (1);
	i = 0;
	while (table->env[i] != NULL)
	{
		cpy[i] = table->env[i];
		i++;
	}
	cpy[i] = cmd.args[1];
	cpy[i + 1] = NULL;
	table->env = cpy;
	return (0);
}