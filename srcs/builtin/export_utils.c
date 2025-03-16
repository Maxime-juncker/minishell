/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:59:03 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/16 15:10:20 by abidolet         ###   ########.fr       */
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

static char	**update_env(char *arg, char **env)
{
	char	**cpy;
	int		i;

	cpy = malloc((arrlen((void **)env) + 2) * sizeof(char *));
	if (malloc_assert(cpy, __FILE__, __LINE__, __FUNCTION__))
		return (env);
	i = -1;
	while (env && env[++i])
	{
		cpy[i] = env[i];
		if (malloc_assert(cpy[i], __FILE__, __LINE__, __FUNCTION__))
			return (free(cpy), env);
	}
	cpy[i] = ft_strdup(arg);
	if (malloc_assert(cpy[i], __FILE__, __LINE__, __FUNCTION__))
		return (free(cpy), env);
	free(env);
	cpy[i + 1] = NULL;
	return (cpy);
}

int	export_env(t_command_table *table, char *arg)
{
	if (ft_strchr(arg, '='))
		table->env = update_env(arg, table->env);
	table->exp = update_env(arg, table->exp);
	if (!table->env || !table->exp)
		return (MALLOC_ERR);
	return (0);
}
