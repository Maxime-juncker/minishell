/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 09:00:06 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_line(char *process_line, int *code)
{
	int	tmp;

	if (!process_line)
		return (1);
	if (!process_line || ft_strcmp(process_line, ":") == 0
		|| ft_strcmp(process_line, "!") == 0)
		return (free(process_line), 0);
	tmp = check_syntax(process_line);
	if (tmp != 0)
	{
		*code = tmp;
		return (free((char *)process_line), 1);
	}
	return (free(process_line), 0);
}
