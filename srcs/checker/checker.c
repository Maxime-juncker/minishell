/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 10:34:34 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_line( const char *process_line, int *code)
{
	int	tmp;

	if (!process_line || ft_strcmp((char *)process_line, ":") == 0
		|| ft_strcmp((char*)process_line, "!") == 0)
		return (free((char *)process_line), 0);
	tmp = check_syntax(process_line);
	if (tmp != 0)
	{
		*code = tmp;
		return (free((char *)process_line), 1);
	}
	return (free((char *)process_line), 0);
}
