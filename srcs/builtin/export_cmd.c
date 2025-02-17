#include "minishell.h"

static int	ft_arraylen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
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
			if (!table.exp[i][j + 1] && n)
				ft_putchar_fd('"', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

static int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

char	**update_env(char *arg, char **env)
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
	cpy[i] = ft_strdup(arg);
	if (!cpy[i])
	{
		cleanup_arr((void **)cpy);
		return (NULL);
	}
	cpy[i + 1] = NULL;
	return (cpy);
}

int	check_arg(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strndup(const char *s, char c)
{
	const char	*start;
	char		*res;
	size_t		i;

	start = s;
	while (*s && *s != c)
		s++;
	res = malloc(s - start + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start != s)
		res[i++] = *start++;
	return (res[i] = 0, res);
}

int	export_cmd(t_command_table *table, t_command cmd)
{
	int	i;

	ft_sort_export(table->exp);
	if (cmd.n_args == 1)
	{
		print_export(*table, cmd.fd_out);
		return (0);
	}
	i = 1;
	while (cmd.args[i] != NULL)
	{
		if (check_arg(cmd.args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd.args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		else
		{
			table->env = unset(table->env, ft_strndup(cmd.args[i], '='));
			table->exp = unset(table->exp, ft_strndup(cmd.args[i], '='));
			if (ft_strchr(cmd.args[i], '='))
				table->env = update_env(cmd.args[i], table->env);
			table->exp = update_env(cmd.args[i], table->exp);
		}
		i++;
	}
	return (0);
}
