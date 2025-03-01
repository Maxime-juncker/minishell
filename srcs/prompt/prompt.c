/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:50 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/01 10:38:26 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

int	handle_process_cmd(t_command_table *table, char *line, int *code);

static int	handle_line_symbol(t_command_table *table, char **args, int *code,
	int i)
{
	char	*process_cmd;

	if (args[i][0] == '(')
	{
		if (handle_process_cmd(table, &args[i][1], code) == MALLOC_ERR)
			return (MALLOC_ERR);
		return (1);
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
		return (1);
	}
	return (0);
}

int	handle_process_cmd(t_command_table *table, char *line, int *code)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split_operators(line);
	if (!args)
		return (MALLOC_ERR);
	while (args[i])
	{
		i += handle_line_symbol(table, args, code, i);
		if (!args[i])
			break ;
		if ((*code == 0 && !ft_strcmp(args[i], "&&"))
			|| (*code != 0 && !ft_strcmp(args[i], "||")))
			i++;
		else if (args[i + 1])
			i += 2;
	}
	cleanup_arr((void **)args);
	return (0);
}

static int	exec_prompt(t_command_table *table, char *line, int *code)
{
	if (!line)
	{
		if (init_table(ft_strdup("exit"), table) == MALLOC_ERR
			|| run_pipeline(table, NULL) == MALLOC_ERR)
			return (MALLOC_ERR);
		return (*code);
	}
	if (ft_strcmp(line, "\n"))
		add_history(line);
	if (check_cmd_line(process_line(line, table->env, &*code), &*code) != 0)
		return (0);
	return (handle_process_cmd(table, line, code));
}

int	new_prompt(t_command_table *table)
{
	char		*line;
	static int	code = 0;
	char		*prompt_char;

	g_signal_received = 0;
	signal(SIGQUIT, SIG_IGN);
	prompt_char = new_prompt_txt(table->env);
	if (!prompt_char)
		return (MALLOC_ERR);
	line = readline(prompt_char);
	free(prompt_char);
	if (g_signal_received)
	{
		code = g_signal_received + 128;
		g_signal_received = 0;
		return (0);
	}
	return (exec_prompt(table, line, &code));
}
