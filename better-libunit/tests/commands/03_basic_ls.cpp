#include "commands.hpp"

t_command	ls_cmd()
{
	t_command	cmd;

	cmd.args = ft_split("ls", ' ');
	cmd.n_args = 1;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	cmd.path = ft_strdup("/usr/bin/ls");

	return (cmd);
}

int	ls_basic( void )
{

	Libunit::Redirect_log();
	run_command(ls_cmd());
	if (Libunit::Check_output("Makefile  better-libunit  bin  includes  libft  obj  srcs\n") == 0)
		return (0);
	else
		return (1);
}
