#include "minishell.h"

int	is_arg(const char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	process_args(char **args, int n)
{
	int	i;
	int	found_args;

	i = 0;
	found_args = 0;
	while (i < n)
	{
		if (is_arg(args[i]) == 1)
		{
			found_args++;
		}
		else
			break ;
		i++;
	}
	return (found_args);
}

// @brief Print the arguments to the standard output.
// @param args The arguments to print (each args are separated by a space).
// @param n The number of arguments.
// @note if args[0] == -n then the function will not print a newline at the end.
// @return 0 if the function succeed, 1 otherwise.
int	echo(char **args, int n)
{
	int	i;
	int	no_br;

	i = process_args(args, n);
	no_br = i;
	while (i < n)
	{
		if (args[i][0] == '\0')
		{
			i++;
			continue ;
		}
		printf("%s", args[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	if (no_br == 0)
		printf("\n");
	return (0);
}
