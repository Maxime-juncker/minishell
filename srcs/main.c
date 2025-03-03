/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:33 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/03 14:48:06 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

static int	exec_prompt(t_command_table *table, char *line, int *code)
{
	t_list	*lst;
	int		res;

	lst = NULL;
	if (check_cmd_line(process_line(line, table->env, &*code), code) != 0)
		return (0);
	res = handle_process_cmd(table, line, code, &lst);
	ft_lstclear(&lst, cleanup_pacakge);
	return (res);
}

int	load_config(t_command_table *table, int *code)
{
	int		fd;
	char	*path;
	char	*line;

	path = find_env_var(table->env, "HOME", NULL);
	if (path == NULL)
		return (0);
	path = ft_strjoin_free(path, "/.minishellrc", FREE1);
	if (malloc_assert(path, __FILE__, __LINE__, __FUNCTION__))
		return (0);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (0);
	table->setup_fd = fd;
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		exec_prompt(table, line, code);
		line = get_next_line(fd);
	}
	close(fd);
	return (*code);
}

int	main(int argc, char **argv, char **env)
{
	t_command_table	table;
	int				code;

	(void)argc;
	init_env(&table, env);
	rl_event_hook = check_interrupt;
	signal(SIGINT, handle_signal);
	signal(SIGPIPE, handle_signal);
	code = 0;
	table.name = get_exec_name(argv[0]);
	table.setup_fd = -1;
	load_config(&table, &code);
	while (code != MALLOC_ERR)
	{
		code = new_prompt(&table);
	}
	cleanup_arr((void **)table.env);
	cleanup_arr((void **)table.exp);
	exit(code);
}
