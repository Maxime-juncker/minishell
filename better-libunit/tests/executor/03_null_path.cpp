#include "executor.hpp"

#include "libunit.hpp"

int	not_found( void )
{
	t_command cmd;
	cmd.args = ft_split("nerjngweoi -l", ' ');
	char** paths = ft_split(getenv("PATH") + 5, ':');

	Libunit::Redirect_log();
	char* path = get_cmd_path(paths, cmd);
	if (path == NULL)
		return (0);
	else
		return (1);
}