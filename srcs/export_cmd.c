#include "minishell.h"

int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

int	set_new_env(t_command_table table)
{

}

int	export_cmd(t_command_table *table, t_command cmd)
{
	char **env;
	char **cpy;
	int		i;
	char	*path;

	env = __environ;

	// cpy env
	cpy = malloc(5000); //? +2 because 1 for the new var and 1 for the final null;
	if (cpy == NULL)
		return (1);
	i = 0;
	while (env[i] != NULL)
	{
		cpy[i] = env[i];
		i++;
	}
	cpy[i] = cmd.args[1];
	cpy[i + 1] = NULL;

	table->env = cpy;
	table->env = NULL;

	return (0);
}