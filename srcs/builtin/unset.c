/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:35:07 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/02 10:31:07 by mjuncker         ###   ########.fr       */
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
	if (malloc_assert(cpy, __FILE__, __LINE__, __FUNCTION__))
		return (*is_malloc_error = 1, env);
	i = -1;
	len = 0;
	while (env[++i] != NULL)
	{
		if (ft_strscmp(env[i], arg, "+="))
		{
			cpy[len] = env[i];
			len++;
		}
		else
			free(env[i]);
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
