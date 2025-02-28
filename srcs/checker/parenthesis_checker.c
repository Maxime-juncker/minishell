/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:41:47 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/28 11:32:44 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	paren_err(const char *line)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	ft_dprintf(2, "%sminishell: syntax error near unexpected token `", RED);
	if (line[i] == '\"' || line[i] == '\'')
	{
		quote = line[i];
		ft_dprintf(2, "%c", line[i]);
		i++;
	}
	while (line[i] && line[i] != quote)
	{
		ft_dprintf(2, "%c", line[i]);
		i++;
	}
	if (quote)
		ft_dprintf(2, "%c", quote);
	ft_dprintf(2, "\'%s\n", RESET);
}

int	parenthesis_valid(const char *line)
{
	int	i;

	i = 1;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == 0 || is_symbol(line[i]))
		return (1);
	paren_err(&line[i]);
	return (0);

}

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
					return (1);
			}
			if (line[i] == ')')
			{
				if (parenthesis_valid(&line[i]) == 0)
					return (2);
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
	if (code == 1)
	{
		ft_dprintf(2, "%sminishell: syntax error near unexpected token `(\'%s\n", RED, RESET);
		return (SYNTAX_ERR);
	}
	return (code);
}
