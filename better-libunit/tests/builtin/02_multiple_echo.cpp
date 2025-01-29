#include "builtin.hpp"

int	echo_multiple( void )
{
	char **args = ft_split("Hello world i am here!", ' ');

	Libunit::Redirect_log();
	echo(args, 5);
	if (Libunit::Check_output("Hello world i am here!\n") == 0)
		return (0);
	else
		return (1);
}
