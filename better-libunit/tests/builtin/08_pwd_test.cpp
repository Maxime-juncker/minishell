#include "builtin.hpp"

int	pwd_test( void )
{
	Libunit::Redirect_log();
	t_command cmd;

	cmd.n_args = 1;
	pwd(cmd);
	char *var = getenv("PWD");
	if (var == NULL)
		std::cout << "NULLL" << std::endl;
	if (Libunit::Check_output(var) == 0)
		return (0);
	else
		return (1);
}
