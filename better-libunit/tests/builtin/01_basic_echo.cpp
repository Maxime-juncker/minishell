#include "builtin.hpp"

int	echo_basic( void )
{
	char **args = ft_split("Hello_world", ' ');

	Libunit::Redirect_log();
	echo(args, 1);
	if (Libunit::Check_output("Hello_world\n") == 0)
		return (0);
	else
		return (1);
}
