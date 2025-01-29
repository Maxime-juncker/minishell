#include "minishell.h"

// @brief Print the arguments to the standard output.
// @param args The arguments to print (each args are separated by a space).
// @param n The number of arguments.
// @note if args[0] == -n then the function will not print a newline at the end.
// @return 0 if the function succeed, 1 otherwise.
int	echo(char **args, int n)
{
	int	i;
	int	no_br;

	i = 0;
	no_br = 0;
	if (n > 0 && ft_strncmp(args[0], "-n", ft_strlen(args[0])) == 0)
	{
		no_br = 1;
		i++;
	}
	while (i < n - 1)
	{
		if (printf("%s ", args[i]) == -1)
			return (1);
		i++;
	}
	if (n == 0)
		printf("\n");
	else if (no_br == 0)
		printf("%s\n", args[i]);
	else
		printf("%s", args[i]);
	return (0);
}
