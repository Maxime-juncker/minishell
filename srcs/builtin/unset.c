/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:35:07 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/26 12:44:34 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_len(char **env, char *arg)
{
	int	len;
	int	diff;

	len = 0;
	diff = 0;
	while (env[len])
	{
		if (arg && !ft_strscmp(env[len], arg, "="))
			diff++;
		len++;
	}
	if (diff == 0)
		return (-1);
	return (len);
}

static char	**unset(char **env, char *arg, int len, int *is_malloc_error)
{
	char	**cpy;
	int		i;

	cpy = malloc((len + 1) * sizeof(char *));
	if (!cpy)
		return (*is_malloc_error = 1, print_malloc_error("unset.c", 38), env);
	i = -1;
	len = 0;
	while (env[++i] != NULL)
	{
		if (ft_strscmp(env[i], arg, "+="))
		{
			cpy[len] = env[i];
			len++;
		}
	}
	free(env);
	cpy[len] = NULL;
	return (cpy);
}

int	unset_if_needed(t_command_table *table, char *arg)
{
	int		len;
	int		is_malloc_error;

	is_malloc_error = 0;
	len = get_env_len(table->env, arg);
	if (len != -1)
		table->env = unset(table->env, arg, len, &is_malloc_error);
	if (is_malloc_error)
		return (MALLOC_ERR);
	len = get_env_len(table->exp, arg);
	if (len != -1)
		table->exp = unset(table->exp, arg, len, &is_malloc_error);
	if (is_malloc_error)
		return (MALLOC_ERR);
	return (0);
}

int	unset_cmd(t_command_table *table, t_command cmd)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		if (unset_if_needed(table, cmd.args[i]) == MALLOC_ERR)
			return (MALLOC_ERR);
		i++;
	}
	return (0);
}
