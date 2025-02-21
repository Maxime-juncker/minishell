/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:15 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:16 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	token_error(char c1, char c2)
{
	ft_dprintf(2, "\033[0;31mminishell: syntax error near unexpected token `%c", c1);
	if (c1 == c2)
		ft_dprintf(2, "%c", c2);
	ft_dprintf(2, "\'\n\033[0m");
	return (SYNTAX_ERR);
}

int	in_base(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}
