#include "builtin.hpp"

int	echo_no_br( void )
{
	char **args = ft_split("-n Hello_world", ' ');

	Libunit::Redirect_log();
	echo(args, 2);
	if (Libunit::Check_output("Hello_world") == 0)
		return (0);
	else
		return (1);
}

