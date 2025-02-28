#include "executor.hpp"

#include "libunit.hpp"

int	null_path( void )
{
	t_command cmd;
	cmd.args = ft_split("nerjngweoi -l", ' ');
	char** paths = ft_split(getenv("PATH") + 5, ':');

	Libunit::Redirect_log();
	get_cmd_path(paths, cmd);
	if (Libunit::Check_output("\033[31mCommand not found\n") == 0)
		return (0);
	else
		return (1);
}