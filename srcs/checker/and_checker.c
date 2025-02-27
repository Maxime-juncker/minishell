/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:29:30 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 15:30:32 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_and_err(const char *line, int i, int reverse, int *occ)
{
	int	text;

	text = 0;
	while (i >= 0 && line[i])
	{
		if (line[i] == '&')
			(*occ)++;
		else if (line[i] != ' ' && line[i] != '>'
			&& line[i] != '<' && line[i] != '|')
		{
			text = 1;
			break ;
		}
		i += 1 * reverse;
	}
	if (text == 0 || *occ > 2)
		return (SYNTAX_ERR);
	return (0);
}

static void	print_err(const char *line, int i)
{
	if ((i > 0 && line[i - 1] == '&') || line[i + 1] == '&')
	{
		ft_dprintf(2,
			"%sminishell: syntax error near unexpected token `&&\'%s\n",
			RED, RESET);
	}
	else
	{
		ft_dprintf(2,
			"%sminishell: syntax error near unexpected token `&\'%s\n",
			RED, RESET);
	}
}

int	check_and_op(const char *line, int index)
{
	int	occ;

	occ = 1;
	if (check_and_err(line, index - 1, -1, &occ) == SYNTAX_ERR)
	{
		print_err(line, index);
		return (SYNTAX_ERR);
	}
	if (check_and_err(line, index + 1, 1, &occ) == SYNTAX_ERR)
	{
		print_err(line, index);
		return (SYNTAX_ERR);
	}
	if (occ == 1)
	{
		print_err(line, index);
		return (SYNTAX_ERR);
	}
	return (0);
}
