/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:50 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/01 12:39:47 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

int	handle_process_cmd(t_command_table *table, char *line, int *code,
		t_list **to_free);

int	handle_line_symbol(t_command_table *table, char *arg, int *code,
		t_list **to_free)
{
	char	*process_cmd;

	if (arg[0] == '(')
	{
		if (handle_process_cmd(table, &arg[1], code, to_free) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else if (ft_strcmp(arg, "&&") && ft_strcmp(arg, "||"))
	{
		process_cmd = process_line(arg, table->env, code);
		if (!process_cmd)
			return (MALLOC_ERR);
		if (!init_table(process_cmd, table))
		{
			*code = run_pipeline(table, *to_free);
			cleanup_table(table);
		}
	}
	return (0);
}

int	handle_process_cmd(t_command_table *table, char *line, int *code,
		t_list **to_free)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split_operators(line);
	if (!args)
		return (MALLOC_ERR);
	ft_lstadd_back(to_free, ft_lstnew(args));
	while (args[i])
	{
		if ((args[i][0] == '(' || (ft_strcmp(args[i], "&&")
				&& ft_strcmp(args[i], "||")))
			&& handle_line_symbol(table, args[i++], code, to_free)
				== MALLOC_ERR)
			return (MALLOC_ERR);
		if (!args[i])
			break ;
		if ((*code == 0 && !ft_strcmp(args[i], "&&"))
			|| (*code != 0 && !ft_strcmp(args[i], "||")))
			i++;
		else if (args[i + 1])
			i += 2;
	}
	return (*code);
}

static int	exec_prompt(t_command_table *table, char *line, int *code)
{
	t_list	*lst;
	int		res;

	lst = NULL;
	if (!line)
	{
		if (init_table(ft_strdup("exit"), table) == MALLOC_ERR
			|| run_pipeline(table, NULL) == MALLOC_ERR)
			return (MALLOC_ERR);
		return (*code);
	}
	if (ft_strcmp(line, "\n"))
		add_history(line);
	if (check_cmd_line(process_line(line, table->env, &*code), code) != 0)
		return (0);
	res = handle_process_cmd(table, line, code, &lst);
	ft_lstclear(&lst, cleanup_pacakge);
	return (res);
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
