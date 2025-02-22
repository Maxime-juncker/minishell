/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:59:03 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/22 10:39:27 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**update_env(char *arg, char **env, int append)
{
	char	**cpy;
	int		i;

	cpy = malloc((arrlen((void **)env) + 2 - append) * sizeof(char *));
	if (cpy == NULL)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		if (append && !ft_strscmp(env[i], arg, "+="))
			cpy[i] = ft_strjoin(env[i], ft_strchr(arg, '=')
					+ (ft_strchr(env[i], '=') != NULL));
		else
			cpy[i] = env[i];
	}
	free(env);
	if (!append)
	{
		cpy[i] = ft_strdup(arg);
		if (!cpy[i])
			return (cleanup_arr((void **)cpy), NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	export(t_command_table *table, char *arg, int append)
{
	if (ft_strchr(arg, '='))
		table->env = update_env(arg, table->env, append);
	table->exp = update_env(arg, table->exp, append);
}
