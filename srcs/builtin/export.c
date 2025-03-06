/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/06 11:06:31 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(char **argv)
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

static int	print_export(char **exp, int fd)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (exp[++i] != NULL)
	{
		dprintf(fd, "export ");
		j = 0;
		n = 0;
		while (exp[i][j])
		{
			dprintf(fd, "%c", exp[i][j]);
			if (exp[i][j] == '=' && !n)
			{
				dprintf(fd, "\"");
				n++;
			}
			if (!exp[i][j + 1] && n)
				dprintf(fd, "\"");
			j++;
		}
		dprintf(fd, "\n");
	}
	return (0);
}

static int	check_arg(char *arg, int *append)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if ((!i && !ft_isalpha(arg[i]) && arg[i] != '_')
			|| (i && (!(ft_isalnum(arg[i]) || arg[i] == '_'
						|| arg[i] == '=' || (arg[i] == '+'
							&& arg[i + 1] == '=')))))
		{
			ft_putstr_fd("\033[0;31mminishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n\033[0m", 2);
			return (1);
		}
		i++;
	}
	if (!i)
		return (1);
	else if (!*append && (arg[i - 1] == '+' && arg[i] == '='))
		(*append)++;
	return (0);
}

int	export_cmd(t_command_table *t, t_command cmd)
{
	int		i;
	int		append;

	if (cmd.n_args == 1)
		return (sort_export(t->exp), print_export(t->exp, cmd.fd_out), 0);
	else if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& t->n_commands)
		return (0);
	sort_export(t->exp);
	i = 0;
	while (cmd.args[++i] != NULL)
	{
		append = 0;
		if (check_arg(cmd.args[i], &append))
			return (1);
		if (!append && unset_if_needed(t, cmd.args[i]) == MALLOC_ERR)
			return (MALLOC_ERR);
		if (append && get_env_len(t->exp, cmd.args[i]) == -1 && !--append)
			cmd.args[i] = ft_strdup_except_char(cmd.args[i], '+');
		if (malloc_assert(cmd.args[i], __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		if (export_env(t, cmd.args[i], append) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (0);
}
