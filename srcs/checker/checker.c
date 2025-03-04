/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/04 12:42:17 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_line(char *process_line, int *code)
{
	int	tmp;

	if (!process_line)
		return (MALLOC_ERR);

	if (ignore_prompt(process_line))
		return (free(process_line), IGNORE);
	tmp = check_syntax(process_line);
	if (tmp != 0)
	{
		*code = tmp;
		return (free(process_line), tmp);
	}
	return (free(process_line), 0);
}
