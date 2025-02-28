#include "builtin.hpp"

int	echo_multiple_no_br( void )
{
	char **args = ft_split("-n Hello world i am here!", ' ');

	Libunit::Redirect_log();
	echo(args, 6);
	if (Libunit::Check_output("Hello world i am here!") == 0)
		return (0);
	else
		return (1);
}
