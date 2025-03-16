/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:49:37 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/16 14:22:37 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	arrlen(void **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**duplicate_env(char **old_env)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (arrlen((void **)old_env) + 1));
	if (malloc_assert(new_env, __FILE__, __LINE__, __FUNCTION__) == MALLOC_ERR)
		return (NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (malloc_assert(new_env[i], __FILE__, __LINE__, __FUNCTION__) != 0)
			return (cleanup_arr((void **)new_env), NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	env(t_command_table table, const t_command cmd)
{
	int	i;

	i = 0;
	while (table.env[i])
	{
		ft_dprintf(cmd.fd_out, "%s\n", table.env[i]);
		i++;
	}
	return (0);
}
