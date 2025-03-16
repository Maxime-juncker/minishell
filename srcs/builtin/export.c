/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/16 15:12:41 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(char **exp, int fd)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (exp[++i] != NULL)
	{
		ft_dprintf(fd, "export ");
		j = 0;
		n = 0;
		while (exp[i][j])
		{
			ft_dprintf(fd, "%c", exp[i][j]);
			if (exp[i][j] == '=' && !n)
			{
				ft_dprintf(fd, "\"");
				n++;
			}
			if (!exp[i][j + 1] && n)
				ft_dprintf(fd, "\"");
			j++;
		}
		ft_dprintf(fd, "\n");
	}
	return (0);
}

static int	check_in_env(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strscmp(env[i], arg, "=")
			&& ft_strlen(arg) == ft_strclen(env[i], '=')
			&& (!ft_strchr(arg, '=') && ft_strchr(env[i], '=')))
			return (1);
		i++;
	}
	return (0);
}

static int	check_arg(t_command_table *t, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && arg[i] != '_')
		{
			ft_dprintf(2, "%sminishell: export: `%s'%s",
				RED, arg, ": not a valid identifier\n", RESET);
			t->code = 1;
			return (1);
		}
		i++;
	}
	if (i == 0 && !arg[i])
	{
		t->code = 1;
		return (1);
	}
	return (0);
}

static int	export(t_command_table *t, t_command cmd)
{
	int	i;

	i = 0;
	while (cmd.args[++i] != NULL)
	{
		if (check_arg(t, cmd.args[i]) || check_in_env(t->env, cmd.args[i]))
			continue ;
		if (unset_if_needed(t, ft_strndup(cmd.args[i], '=')) != 0)
			return (MALLOC_ERR);
		if (malloc_assert(cmd.args[i], __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		if (export_env(t, cmd.args[i]) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (0);
}

int	export_cmd(t_command_table *t, t_command cmd)
{
	if (cmd.n_args == 1)
		return (sort_export(t->exp), print_export(t->exp, cmd.fd_out), 0);
	else if ((cmd.fd_in != STDIN_FILENO || cmd.fd_out != STDOUT_FILENO)
		&& t->n_commands)
		return (0);
	else if (cmd.n_args == 2 && cmd.args[1][0] == '-' && cmd.args[1][1])
	{
		ft_dprintf(2, "%sminishell: export: -%c: %s or export -p%s\n",
			RED, cmd.args[1][1],
			"invalid option\nexport: usage: export [-fn] [name[=value] ...]",
			RESET);
		return (1);
	}
	sort_export(t->exp);
	export(t, cmd);
	return (t->code);
}
