/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:04 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:05 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_arg(const char *arg)
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

static int	process_args(char **args, int n)
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

int	echo(char **args, int n)
{
	int	i;
	int	no_br;

	i = process_args(args, n);
	no_br = i;
	while (i < n)
	{
		printf("%s", args[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	if (no_br == 0)
		printf("\n");
	return (0);
}
