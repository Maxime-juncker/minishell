/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:58:06 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/11 16:50:26 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	ft_count_words(const char *s, char c)
{
	int	res;
	int	in_word;
	int	in_quote;

	res = 0;
	in_word = 0;
	in_quote = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			in_quote = toggle_quote(*s, in_quote);
		if (*s == c && !in_quote)
			in_word = 0;
		else if (!in_word)
		{
			res++;
			in_word = 1;
		}
		s++;
	}
	return (res);
}

static char	*ft_strndup2(const char *s, char c)
{
	const char	*start;
	char		*res;
	size_t		i;
	int			in_quote;

	start = s;
	in_quote = 0;
	while (*s && (*s != c || in_quote))
	{
		if (*s == '\'' || *s == '\"')
			in_quote = toggle_quote(*s, in_quote);
		s++;
	}
	res = malloc(s - start + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start != s)
		res[i++] = *start++;
	res[i] = 0;
	return (res);
}

void	free_all(char **res, int i)
{
	while (--i != -1)
		free(res[i]);
	free(res);
}

int	do_split(char *s, char c, char **res)
{
	char	in_quote;
	int		i;

	i = 0;
	in_quote = 0;
	while (*s)
	{
		while (*s == c && !in_quote)
			s++;
		if (!*s)
			break ;
		res[i] = ft_strndup2(s, c);
		if (!res[i++])
			return (free(s), free_all(res, i), MALLOC_ERR);
		while (*s && (*s != c || in_quote))
		{
			if (*s == '\'' || *s == '\"')
				in_quote = toggle_quote(*s, in_quote);
			s++;
		}
	}
	return (i);
}

char	**ft_split_pipe(char *s)
{
	char	**res;
	int		i;
	char	c;

	c = '|';
	res = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	i = do_split(s, c, res);
	free(s);
	if (i == MALLOC_ERR)
		return (NULL);
	res[i] = NULL;
	return (res);
}
