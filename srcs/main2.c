#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	pipex(argv, env);
	return (0);
}