/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/10 12:08:48 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

#if DEBUG

void	show_table(t_command_table table)
{
	size_t	i;

	i = 0;
	ft_printf("%sn_command: %zu\n", GRAY, table.n_commands);
	while (i < table.n_commands)
	{
		ft_printf("%s%s:\n", GRAY, table.commands[i].args[0]);
		ft_printf("  fd: in (%d) out (%d)\n", \
				table.commands[i].fd_in, table.commands[i].fd_out);
		ft_printf("%s", RESET);
		i++;
	}
}

void	show_cmd(t_command cmd)
{
	size_t	i;

	ft_printf("%srunning %s (%zu args)\nargs: ", GRAY, cmd.args[0], cmd.n_args);
	i = 0;
	while (i < cmd.n_args)
	{
		ft_printf("[%s]", cmd.args[i]);
		i++;
	}
	ft_printf("\nfd_in(%d)\tfd_out(%d)%s\n", cmd.fd_in, cmd.fd_out, RESET);
}

#else

void	show_table(t_command_table table)
{
	(void)table;
}

void	show_cmd(t_command cmd)
{
	(void)cmd;
}

#endif
