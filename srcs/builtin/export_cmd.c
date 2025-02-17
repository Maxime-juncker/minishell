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

int	print_export(t_command_table table)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	while (table.exp[i] != NULL)
	{
		printf("export ");
		j = 0;
		n = 0;
		while (table.exp[i][j])
		{
			printf("%c", table.exp[i][j]);
			if (table.exp[i][j] == '=' && !n)
			{
				printf("%c", '"');
				n++;
			}
			else if (!table.exp[i][j + 1])
				printf("\"\n");
			j++;
		}
		i++;
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

int	export_cmd(t_command_table *table, t_command cmd)
{
	char	**cpy;
	int		i;

	ft_sort_export(table->exp);
	if (cmd.n_args == 1)
	{
		print_export(*table);
		return (0);
	}
	cpy = malloc((ft_arraylen(table->exp) + 2) * sizeof(char *));
	if (cpy == NULL)
		return (MALLOC_ERR);
	i = 0;
	while (table->exp[i] != NULL)
	{
		cpy[i] = table->exp[i];
		i++;
	}
	cpy[i] = ft_strdup(cmd.args[1]);
	cpy[i + 1] = NULL;
	table->exp = cpy;
	return (0);
}
