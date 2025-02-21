/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:00 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/21 17:30:02 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void	init_env(t_command_table *table, char **env)
{
	table->env = duplicate_env(env);
	if (table->env == NULL)
		exit(EXIT_FAILURE);
	table->exp = duplicate_env(env);
	if (table->exp == NULL)
	{
		cleanup_arr((void **)table->env);
		exit(EXIT_FAILURE);
	}
}

void	handle_signal(int signal)
{
	g_signal_received = signal;
}

void	cleanup_table(t_command_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_commands)
	{
		cleanup_arr((void **)table->commands[i].args);
		i++;
	}
	free(table->commands);
}

char	*get_folder(void)
{
	char	*temp;
	char	buffer[1024];
	char	*folder;

	if (!getcwd(buffer, sizeof(buffer)))
		return (ft_strdup(""));
	folder = ft_strdup(buffer);
	if (!folder)
		return (NULL);
	temp = folder;
	if (folder[1] != '\0')
	{
		while (*folder && ft_strchr(folder, '/') != 0)
		{
			folder++;
		}
	}
	folder = ft_strjoin(folder, ":");
	free(temp);
	return (folder);
}

int	ignore_prompt(char *prompt)
{
	while (*prompt)
	{
		if (!(*prompt == ' ' || (*prompt >= 9 && *prompt <= 13))
			&& in_base(*prompt, ":!") == -1)
			return (0);
		prompt++;
	}
	return (1);
}
