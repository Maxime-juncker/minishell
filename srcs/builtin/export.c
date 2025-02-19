#include "minishell.h"

void	ft_sort_export(char **argv)
{
	int		i;
	int		diff;
	char	*temp;
	int		size;

	diff = 1;
	size = arrlen((void **)argv);
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

char	**update_env(char *arg, char **env)
{
	char	**cpy;
	int		i;

	cpy = malloc((arrlen((void **)env) + 2) * sizeof(char *));
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
		free(env);
		return (NULL);
	}
	cpy[i + 1] = NULL;
	free(env);
	return (cpy);
}

int	check_arg(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd("\033[0;31mminishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n\033[0m", 2);
		return (1);
	}
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
		{
			ft_putstr_fd("\033[0;31mminishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n\033[0m", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_cmd(t_command_table *table, t_command cmd)
{
	int		i;
	char	*temp;

	if (cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		return (0);
	ft_sort_export(table->exp);
	if (cmd.n_args == 1)
		return (print_export(*table, cmd.fd_out), 0);
	i = 1;
	while (cmd.args[i] != NULL)
	{
		if (check_arg(cmd.args[i]))
			return (1);
		temp = ft_strndup(cmd.args[i], '=');
		if (!temp)
			return (MALLOC_ERR);
		handle_cmd(table, temp);
		free(temp);
		if (table->env == NULL || table->exp == NULL)
			return (MALLOC_ERR);
		if (ft_strchr(cmd.args[i], '='))
			table->env = update_env(cmd.args[i], table->env);
		table->exp = update_env(cmd.args[i], table->exp);
		i++;
	}
	return (0);
}
