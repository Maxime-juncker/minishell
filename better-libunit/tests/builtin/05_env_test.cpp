#include "builtin.hpp"

int	env_test( void )
{
	Libunit::Redirect_log();
	env();
	if (Libunit::Check_output("") != 0)
		return (0);
	else
		return (1);
}
