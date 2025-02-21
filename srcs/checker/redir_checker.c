/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:27 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:28 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_line_error(const char *str, const char last)
{
	if (last == '|')
		return (token_error('|', *(str - 2)));
	if (last == '>' || last == '<')
	{
		ft_dprintf(2, "\033[0;31mminishell: syntax error near unexpected token %s",
			"`newline\'\n\033[0m");
		return (SYNTAX_ERR);
	}
	return (0);
}

char	*remove_quotes_pair(char *s)
{
	char	*tmp;
	char	quote;
	int		i;

	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	quote = 0;
	i = 0;
	while (*s)
	{
		if (*s == quote)
		{
			quote = 0;
			s++;
			continue ;
		}
		else if (quote == 0 && (*s == '\'' || *s == '\"'))
		{
			quote = *s++;
			continue ;
		}
		tmp[i++] = *s++;
	}
	return (tmp);
}

static char	*get_file_name(const char *s)
{
	int		i;
	char	quote;
	char	*file;
	int		start;
	char	*res;

	i = 0;
	quote = 0;
	start = 0;
	while (s[start] == ' ' || s[start] == '>' || s[start] == '<')
		start++;
	i = start;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			quote = toggle_quote(quote, s[i]);
		if (s[i] == ' ' && !quote)
			break ;
		i++;
	}
	file = ft_substr(s, start, i - start);
	if (!file)
		return (NULL);
	res = remove_quotes_pair(file);
	return (free(file), res);
}

static int	skip_check_in(const char *cmd_line, int i)
{
	if (i > 0)
	{
		if (cmd_line[i + 1] == '<' || cmd_line[i - 1] == '<'
			|| cmd_line[i + 1] == '>' || cmd_line[i + 1] == '\0')
			return (1);
	}
	else if (cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>'
		|| cmd_line[i + 1] == '\0')
		return (1);
	while (cmd_line[i] == ' ')
		i++;
	if (cmd_line[i] == '\0')
		return (1);
	return (0);
}

int	check_redir_in(const char *cmd_line, int i)
{
	char	*file;

	if (skip_check_in(cmd_line, i))
		return (0);
	file = get_file_name(cmd_line + i);
	if (file == NULL)
	{
		return (new_line_error(cmd_line + i, '<'));
	}
	if (access(file, F_OK) == -1)
	{
		ft_dprintf(2, "\033[0;31mminishell: %s: No such file or directory\n\033[0m",
			file);
		free(file);
		return (1);
	}
	free(file);
	return (0);
}
