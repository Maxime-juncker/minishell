#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	run_pipeline(example_table(env));
	return (0);
}