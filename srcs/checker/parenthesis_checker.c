/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:41:47 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/28 10:25:40 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	check_unclosed(const char *line)
{
	int	paren;
	int	quote;
	int	i;

	paren = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		quote = toggle_quote(line[i], quote);
		if (!quote)
		{
			if (line[i] == '(')
				paren++;
			else if (line[i] == ')')
			{
				paren--;
				if (paren < 0)
					break;
			}
		}
		i++;
	}
	return (paren);
}

// int	parenthesis_valid(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
		
// 		i++;
// 	}
// }

int	check_content(const char *line)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (line[i])
	{
		quote = toggle_quote(line[i], quote);
		if (!quote)
		{
			if (line[i] == '(')
			{
				i++;
				while (line[i] && is_whitespace(line[i]))
					i++;
				if (line[i] == ')')
					return (SYNTAX_ERR);
			}
			if (line[i] == ')')
			{
				// if (parenthesis_valid(&line[i]) == 0)
				// 	return (SYNTAX_ERR);
			}
		}
		i++;
	}
	return (0);
}

int	check_parenthesis(const char *line)
{
	int	code;

	code = check_unclosed(line);
	if (code > 0)
	{
		ft_dprintf(2, "%sminishell: syntax error near unexpected token `)\'%s\n", RED, RESET);
		return (SYNTAX_ERR);
	}
	else if (code < 0)
	{
		ft_dprintf(2, "%sminishell: syntax error near unexpected token `(\'%s\n", RED, RESET);
		return (SYNTAX_ERR);
	}
	code = check_content(line);
	if (code == SYNTAX_ERR)
	{
		ft_dprintf(2, "%sminishell: syntax error near unexpected token `(\'%s\n", RED, RESET);
		return (SYNTAX_ERR);
	}
	return (0);
}
