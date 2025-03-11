/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:50 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/11 10:03:21 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

static int	handle_process_cmd(t_command_table *table, char *line, int *code,
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
		if (malloc_assert(process_cmd, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		// if (check_cmd_line(process_cmd, table->code))
		if (!init_table(process_cmd, table))
		{
			*code = run_pipeline(table, *to_free);
			cleanup_table(table);
		}
	}
	return (0);
}

static int	handle_process_cmd(t_command_table *table, char *line, int *code,
		t_list **to_free)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split_operators(line);
	if (malloc_assert(args, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	if (ft_lstadd_back(to_free, ft_lstnew(args)) == -1)
		return (ft_lstclear(to_free, cleanup_pacakge), MALLOC_ERR);
	while (args[i])
	{
		if ((args[i][0] == '(' || (ft_strcmp(args[i], "&&")
				&& ft_strcmp(args[i], "||"))) && MALLOC_ERR ==
				handle_line_symbol(table, args[i++], code, to_free))
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

static int	exec_prompt(t_command_table *table, char *line)
{
	t_list	*lst;
	int		res;

	lst = NULL;
	if (!line)
	{
		if (init_table(ft_strdup("exit"), table) == MALLOC_ERR
			|| run_pipeline(table, NULL) == MALLOC_ERR)
			return (MALLOC_ERR);
		return (table->code);
	}
	add_history(line);
	if (check_cmd_line(process_line(line, table->env, &table->code),
			&table->code) != 0)
		return (0);
	res = handle_process_cmd(table, line, &table->code, &lst);
	ft_lstclear(&lst, cleanup_pacakge);
	return (res);
}

int	new_prompt(t_command_table *table)
{
	char		*line;
	char		*prompt_char;
	int			res;

	g_signal_received = 0;
	res = 0;
	signal(SIGQUIT, SIG_IGN);
	prompt_char = new_prompt_txt(table->env);
	if (!prompt_char)
		return (MALLOC_ERR);
	line = readline(prompt_char);
	free(prompt_char);
	remove_unnecessary_parentheses(line);
	if (g_signal_received)
	{
		free(line);
		table->code = g_signal_received + 128;
		g_signal_received = 0;
		return (0);
	}
	if (!line || (line && line[0] != '\0'))
		res = exec_prompt(table, line);
	free(line);
	return (res);
}
