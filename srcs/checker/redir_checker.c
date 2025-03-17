/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:27 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/17 10:36:00 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_line_error(const char *str, const char last)
{
	if (last == '|')
		return (token_error('|', *(str - 2)));
	if (last == '>' || last == '<')
	{
		ft_dprintf(2, "%sminishell: syntax error near unexpected token %s%s",
			RED, "`newline\'\n", RESET);
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
	if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
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
	if (malloc_assert(file, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	res = remove_quotes_pair(file);
	return (free(file), res);
}

int	check_redir_in(const char *cmd_line, int i)
{
	char	*file;

	if (i != -1)
		file = get_file_name(cmd_line + i);
	else
		file = ft_strdup(cmd_line);
	if (!file)
		return (NOT_FOUND);
	if (access(file, F_OK) == -1)
	{
		ft_dprintf(2, "%sminishell: %s: No such file or directory\n%s",
			RED, file, RESET);
		free(file);
		return (NOT_FOUND);
	}
	if (access(file, R_OK) == -1)
	{
		ft_dprintf(2, "%sminishell: %s: Permission denied\n%s",
			RED, file, RESET);
		free(file);
		return (1);
	}
	free(file);
	return (0);
}
