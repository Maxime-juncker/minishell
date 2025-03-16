/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:33 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/07 14:29:43 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

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
	load_config(&table);
	table.code = 0;
	table.setup_fd = -1;
	while (code != MALLOC_ERR)
	{
		code = new_prompt(&table);
	}
	cleanup_arr((void **)table.env);
	cleanup_arr((void **)table.exp);
	exit(code);
}
