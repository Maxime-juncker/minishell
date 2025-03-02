/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:49:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/02 22:26:08 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

static int	is_operator(const char *s)
{
	return ((s[0] == '&' && s[1] == '&') || (s[0] == '|' && s[1] == '|'));
}

static char	*ft_strndup2(const char *s, size_t n)
{
	char	*res;
	size_t	i;

	res = malloc(n + 1);
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__) == MALLOC_ERR)
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	*handle_string(const char **s)
{
	size_t	len;
	char	in_quote;

	len = 0;
	in_quote = 0;
	while ((*s)[len] && (*s)[len] != '(')
	{
		if ((*s)[len] == '\'' || (*s)[len] == '\"')
			in_quote = toggle_quote((*s)[len], in_quote);
		if (in_quote == 0 && is_operator(*s + len))
			break ;
		len++;
	}
	return (ft_strndup2(*s, len));
}

static char	*handle_parentheses(const char **s, int *paren_count)
{
	size_t	len;

	(*paren_count)++;
	len = 1;
	while ((*s)[len] && ((*s)[len] != ')' || *paren_count > 1))
	{
		if ((*s)[len] == '(')
			(*paren_count)++;
		else if ((*s)[len] == ')')
			(*paren_count)--;
		len++;
	}
	return (ft_strndup2(*s, len));
}

char	**ft_split_operators(const char *s)
{
	char	**res;
	int		i;
	int		paren_count;

	res = ft_calloc(ft_strlen(s) + 1, sizeof(char *));
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__) == MALLOC_ERR)
		return (NULL);
	i = 0;
	paren_count = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == '(')
			res[i] = handle_parentheses(&s, &paren_count);
		else if (is_operator(s))
			res[i] = ft_strndup2(s, 2);
		else if (*s)
			res[i] = handle_string(&s);
		if (!res[i++])
			return (free_all(res, i), NULL);
		s += ft_strlen(res[i - 1]);
		s += (*s == ')');
	}
	return (res[i] = NULL, res);
}
