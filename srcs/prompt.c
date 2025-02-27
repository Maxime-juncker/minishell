/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:50 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/27 10:06:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

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

static char	*get_folder(void)
{
	char	*temp;
	char	buffer[1024];
	char	*folder;

	if (!getcwd(buffer, sizeof(buffer)))
	{
		temp = ft_strdup("");
		if (!temp)
			return (malloc_assert(ERR), NULL);
		return (temp);
	}
	folder = ft_strdup(buffer);
	if (!folder)
		return (malloc_assert(ERR), NULL);
	temp = folder;
	if (folder[1] != '\0')
		while (*folder && ft_strchr(folder, '/') != 0)
			folder++;
	folder = ft_strjoin(folder, ":");
	free(temp);
	if (!folder)
		return (malloc_assert(ERR), NULL);
	return (folder);
}

static char	*new_prompt_txt(char **env)
{
	char	*txt;
	char	*folder;

	folder = get_folder();
	if (!folder)
		return (malloc_assert(ERR), NULL);
	txt = ft_strjoin_free(BLUE, folder, FREE2);
	if (!txt)
		return (malloc_assert(ERR), NULL);
	txt = ft_charjoin(txt, ' ');
	if (!txt)
		return (malloc_assert(ERR), NULL);
	txt = ft_strjoin_free(txt, GREEN, FREE1);
	if (!txt)
		return (malloc_assert(ERR), NULL);
	txt = ft_strjoin_free(txt, find_env_var(env, "USER", NULL), FREE1 | FREE2);
	if (!txt)
		return (malloc_assert(ERR), NULL);
	txt = ft_strjoin_free(txt, "$\033[0m ", FREE1);
	if (!txt)
		return (malloc_assert(ERR), NULL);
	return (txt);
}

int	handle_process_cmd(t_command_table *table, char *line, int *code, int rec)
{
	char	**args;
	char	*process_cmd;
	int		i;

	i = 0;
	args = ft_split_operators(line);
	if (!rec)
		free(line);
	if (!args)
		return (MALLOC_ERR);
	while (args[i])
	{
		if (args[i][0] == '(')
		{
			if (handle_process_cmd(table, &args[i][1], code, 1) == MALLOC_ERR)
				return (MALLOC_ERR);
			i++;
		}
		else if (ft_strcmp(args[i], "&&") && ft_strcmp(args[i], "||"))
		{
			process_cmd = process_line(args[i], table->env, code);
			if (!process_cmd)
				return (MALLOC_ERR);
			if (!process_cmd && *code == MALLOC_ERR)
				return (free(process_cmd), MALLOC_ERR);
			if (!init_table(process_cmd, table))
			{
				*code = run_pipeline(table, args);
				cleanup_table(table);
			}
			i++;
		}
		if (!args[i])
			break ;
		if ((*code == 0 && !ft_strcmp(args[i], "&&")) || (*code != 0 && !ft_strcmp(args[i], "||")))
			i++;
		else if (args[i + 1])
			i += 2;
	}
	cleanup_arr((void **)args);
	return (0);
}

int	new_prompt(t_command_table *table)
{
	char		*line;
	static int	code = 0;
	char		*prompt_char;

	g_signal_received = 0;
	prompt_char = new_prompt_txt(table->env);
	if (!prompt_char)
		return (MALLOC_ERR);
	line = readline(prompt_char);
	free(prompt_char);
	if (g_signal_received)
	{
		if (g_signal_received == SIGINT)
			code = 130;
		g_signal_received = 0;
		return (0);
	}
	if (!line)
	{
		if (init_table(ft_strdup("exit"), table) == MALLOC_ERR || run_pipeline(table, NULL) == MALLOC_ERR)
			return (MALLOC_ERR);
		return (code);
	}
	if (ft_strcmp(line, "\n"))
		add_history(line);
	if (check_cmd_line(process_line(line, table->env, &code), &code) == 1)
		return (MALLOC_ERR);
	return (handle_process_cmd(table, line, &code, 0));
}
