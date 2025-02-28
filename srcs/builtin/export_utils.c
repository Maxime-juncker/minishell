/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:59:03 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/27 16:58:38 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_assert(void *mem, const char *file, int line, const char *function)
{
	if (mem)
		return (0);
	ft_dprintf(2, "%s%s:%d: %sminishell: malloc assertion failed in %s'%s'\n",
		GRAY, file, line, RED, RESET, function);
	return (MALLOC_ERR);
}

static char	**update_env(char *arg, char **env, int append)
{
	char	**cpy;
	int		i;

	cpy = malloc((arrlen((void **)env) + 2 - append) * sizeof(char *));
	if (!cpy)
		return (malloc_assert(NULL, __FILE__, __LINE__, __FUNCTION__), env);
	i = -1;
	while (env && env[++i])
	{
		if (append && !ft_strscmp(env[i], arg, "+="))
			cpy[i] = ft_strjoin_free(env[i], ft_strchr(arg, '=')
					+ (ft_strchr(env[i], '=') != NULL), FREE1);
		else
			cpy[i] = env[i];
		if (!cpy[i])
			return (free(cpy), malloc_assert(NULL, __FILE__, __LINE__, __FUNCTION__), env);
	}
	if (!append)
	{
		cpy[i] = ft_strdup(arg);
		if (!cpy[i++])
			return (free(cpy), malloc_assert(NULL, __FILE__, __LINE__, __FUNCTION__), env);
	}
	free(env);
	return (cpy[i] = NULL, cpy);
}

int	export_env(t_command_table *table, char *arg, int append)
{
	if (ft_strchr(arg, '='))
		table->env = update_env(arg, table->env, append);
	table->exp = update_env(arg, table->exp, append);
	if (!table->env || !table->exp)
		return (MALLOC_ERR);
	return (0);
}
