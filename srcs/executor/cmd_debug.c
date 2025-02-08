#include "minishell.h"

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

#if DEBUG

void	show_table(t_command_table table)
{
	int	i;

	i = 0;
	while (i < table.n_commands)
	{
		printf("%s%s:\n", GRAY, table.commands[i].args[0]);
		printf("  fd: in (%d) out (%d)\n", \
				table.commands[i].fd_in, table.commands[i].fd_out);
		printf("%s", RESET);
		i++;
	}
}

void	show_cmd(t_command cmd)
{
	int	i;

	printf("%srunning %s (%zu args)\nargs: ", GRAY, cmd.args[0], cmd.n_args);
	i = 0;
	while (i < cmd.n_args)
	{
		printf("[%s]", cmd.args[i]);
		i++;
	}
	printf("\nfd_in(%d)\tfd_out(%d)%s\n", cmd.fd_in, cmd.fd_out, RESET);
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
