/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:23 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:24 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(const char *cmd_line)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		{
			if (quote == 0)
				quote = cmd_line[i];
			else if (quote == cmd_line[i])
				quote = 0;
		}
		i++;
	}
	if (quote == 0)
		return (0);
	ft_dprintf(2, "%sminishell: syntax error missing `%c\' quote%s\n",
		RED, quote, RESET);
	return (SYNTAX_ERR);
}
