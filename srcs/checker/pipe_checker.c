/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:15:46 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 16:56:46 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(const char *line, int index)
{
	int	i;
	int	code;

	code = check_token_error(line, index, 2, '|');
	if (code != 0)
		return (code);
	i = index - 1;
	while (i >= 0)
	{
		if (is_symbol(line[i]) && line[i] != '|')
			return (token_error('|', 0));
		if (!is_whitespace(line[i]))
			return (0);
		i--;
	}
	return (0);
}
