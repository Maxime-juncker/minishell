/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:49:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/28 10:32:50 by abidolet         ###   ########.fr       */
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
	if (!res)
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

char	**ft_split_operators(const char *s)
{
	char	**res;
	int		i;
	size_t	len;
	int		paren_count;
	char	in_quote;

	if (!s)
		return (NULL);
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	paren_count = 0;
	in_quote = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == '(')
		{
			paren_count++;
			len = 1;
			while (s[len] && (s[len] != ')' || paren_count > 1))
			{
				if (s[len] == '(')
					paren_count++;
				else if (s[len] == ')')
					paren_count--;
				len++;
			}
			res[i] = ft_strndup2(s, len);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += len;
			if (*s == ')')
				s++;
		}
		else if (is_operator(s))
		{
			res[i] = ft_strndup2(s, 2);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += 2;
		}
		else if (*s)
		{
			len = 0;
			while (s[len] && s[len] != '(')
			{
				if (s[len] == '\'' || s[len] == '\"')
					in_quote = toggle_quote(s[len], in_quote);
				if (in_quote == 0 && is_operator(s + len))
					break ;
				len++;
			}
			res[i] = ft_strndup2(s, len);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += len;
		}
	}
	res[i] = NULL;
	return (res);
}
