/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:32 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 14:41:57 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_symbol(char error_symb, const char *cmd_line, int i)
{
	int	occ;
	int	max_occ;

	if (error_symb == '<' && cmd_line[i + 1] == '>')
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `<>\'\n");
		return (SYNTAX_ERR);
	}
	max_occ = 2;
	occ = 0;
	ft_dprintf(2, "\033[0;31mminishell: syntax error near unexpected token `");
	while (cmd_line[i] == error_symb && occ < max_occ)
	{
		ft_dprintf(2, "%c", error_symb);
		i++;
		occ++;
	}
	ft_dprintf(2, "\'\n\033[0m");
	return (SYNTAX_ERR);
}

static int	check_redir_out(const char *cmd_line, int i)
{
	char	error_symb;
	int		j;

	j = i - 1;
	if (i == 0)
		j = 0;
	i++;
	if (cmd_line[i] == '>')
		return (0);
	while (j >= 0 && is_whitespace(cmd_line[j]))
		j--;
	if (cmd_line[j] == '<')
		return (token_error('>', 0));
	while (cmd_line[i])
	{
		if (cmd_line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (cmd_line[i] != '|' && cmd_line[i] != '<'
			&& cmd_line[i] != '>' && cmd_line[i] != '&')
			return (0);
		error_symb = cmd_line[i];
		return (error_symbol(error_symb, cmd_line, i));
	}
	return (0);
}

static int	check_error(const char *cmd_line, int i)
{
	char	to_find;
	int		code;

	to_find = cmd_line[i];
	if (to_find == '>')
	{
		code = check_token_error(cmd_line, i, 2, '>');
		if (code != 0)
			return (code);
		return (check_redir_out(cmd_line, i));
	}
	if (to_find == '<')
	{
		code = check_token_error(cmd_line, i, 2, '<');
		if (code != 0)
			return (code);
		return (check_redir_in(cmd_line, i));
	}
	if (to_find == '|')
		return (check_token_error(cmd_line, i, 2, '|'));
	if (to_find == '&')
		return (check_and_op(cmd_line, i));
	return (0);
}

static int	check_line(const char *cmd_line)
{
	int		i;
	char	last;
	char	quote;
	int		code;

	i = 0;
	last = 0;
	quote = 0;
	while (cmd_line[i])
	{
		quote = toggle_quote(cmd_line[i], quote);
		if (!quote && (cmd_line[i] == '<' || cmd_line[i] == '>'
				|| cmd_line[i] == '|' || cmd_line[i] == '&'))
		{
			code = check_error(cmd_line, i);
			if (code != 0)
				return (code);
		}
		if (!quote && cmd_line[i] != ' ')
			last = cmd_line[i];
		i++;
	}
	if (new_line_error(cmd_line + i, last) == SYNTAX_ERR)
		return (SYNTAX_ERR);
	return (0);
}

int	check_syntax(const char *cmd_line)
{
	int	i;
	int	code;

	code = check_quotes(cmd_line);
	if (code != 0)
		return (code);
	code = check_parenthesis(cmd_line);
	if (code != 0)
		return (code);
	i = 0;
	while (cmd_line[i] == ' ')
		i++;
	if (cmd_line[i] == '|' && cmd_line[i + 1] != '|')
		return (token_error('|', '\0'));
	return (check_line(cmd_line + i));
}
