#include "executor.hpp"

int	test_path( void )
{
	char** paths = ft_split(getenv("PATH") + 5, ':');
	std::string	path = get_cmd_path(paths, example_cmd());

	if (path == "/usr/bin/ls")
		return (0);
	else
		return (1);
}