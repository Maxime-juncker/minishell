/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:01 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 10:25:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	overflow_feedback(int overflow, void *param)
{
	*(int *)param = overflow;
}

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' && s[1] != '\0')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	get_code(t_command cmd)
{
	int	nb;
	int	code;

	if (cmd.n_args == 1)
		return (0);
	code = 0;
	nb = overflow_check(cmd.args[1], &overflow_feedback, &code);
	if (code != 0 || is_number(cmd.args[1]) == 0)
	{
		ft_dprintf(2, "%sminishell: exit: %s: numeric argument required%s\n",
			RED, cmd.args[1], RESET);
		return (2);
	}
	else if (cmd.n_args > 2)
	{
		ft_dprintf(2, "%sminishell: exit: too many arguments%s\n", RED, RESET);
		return (2);
	}
	return (nb);
}

void	exit_shell(t_command_table *table, t_command cmd, t_free_package package)
{
	int	code;

	if (table->n_commands > 1)
		return ;
	free(package.childs);
	cleanup_arr((void **)package.args);
	code = get_code(cmd);
	cleanup_arr((void **)table->env);
	cleanup_arr((void **)table->exp);
	cleanup_table(table);
	printf("exit\n");
	exit(code);
}
