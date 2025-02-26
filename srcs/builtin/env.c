/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:26 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/26 08:55:44 by abidolet         ###   ########.fr       */
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
	if (!new_env)
		return (print_malloc_error("env.c", 32), NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
			return (print_malloc_error("env.c", 38),
				cleanup_arr((void **)new_env), NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	env(t_command_table table)
{
	int	i;

	i = 0;
	while (table.env[i])
	{
		printf("%s\n", table.env[i]);
		i++;
	}
	return (0);
}
