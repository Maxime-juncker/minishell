#include "minishell.h"

static int	ft_arraylen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	ft_sort_export(char **argv)
{
	int		i;
	int		diff;
	char	*temp;
	int		size;

	diff = 1;
	size = ft_arraylen(argv);
	while (diff)
	{
		i = 0;
		diff = 0;
		while (i < (size - 1))
		{
			if (ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				temp = argv[i];
				argv[i] = argv[i + 1];
				argv[i + 1] = temp;
				diff = 1;
			}
			i++;
		}
	}
}

int	print_export(t_command_table table, int fd)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (table.exp[++i] != NULL)
	{
		ft_putstr_fd("export ", fd);
		j = 0;
		n = 0;
		while (table.exp[i][j])
		{
			ft_putchar_fd(table.exp[i][j], fd);
			if (table.exp[i][j] == '=' && !n)
			{
				ft_putchar_fd('"', fd);
				n++;
			}
			else if (!table.exp[i][j + 1] && n)
				ft_putchar_fd('"', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

// +2 because 1 for the new var and 1 for the final null;
static int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

char	**update_env(t_command cmd, char **env)
{
	char	**cpy;
	int		i;

	cpy = malloc((ft_arraylen(env) + 2) * sizeof(char *));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		cpy[i] = env[i];
		i++;
	}
	cpy[i] = ft_strdup(cmd.args[1]);
	if (!cpy[i])
	{
		cleanup_arr((void **)cpy);
		return (NULL);
	}
	cpy[i + 1] = NULL;
	return (cpy);
}

int	export_cmd(t_command_table *table, t_command cmd)
{
	ft_sort_export(table->exp);
	if (cmd.n_args == 1)
	{
		print_export(*table, cmd.fd_out);
		return (0);
	}
	if (ft_strchr(cmd.args[1], '='))
		table->env = update_env(cmd, table->env);
	table->exp = update_env(cmd, table->exp);
	return (0);
}
