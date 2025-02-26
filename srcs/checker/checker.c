/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 09:08:32 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_line( const char *process_line, int *code)
{
	int	tmp;

	if (!process_line || ft_strcmp((char *)process_line, ":") == 0
		|| ft_strcmp((char*)process_line, "!") == 0)
		return (0);
	tmp = check_syntax(process_line);
	if (tmp != 0)
	{
		*code = tmp;
		return (1);
	}
	return (0);
}
