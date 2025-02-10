/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_1space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:20:53 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/10 13:56:49 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	rep;
	int	i;

	rep = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			rep++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
		{
			i++;
			if (s[i] && s[i] == c)
			{
				rep++;
				while (s[i] && s[i] == c)
					i++;
			}
		}
	}
	return (rep);
}

static char	*ft_strndup(const char *s, char c)
{
	const char	*start;
	char		*res;
	size_t		i;

	start = s;
	if (*s != c)
		while (*s && *s != c)
			s++;
	else
		while (*(s + 1) && *(s + 1) == c)
			s++;
	res = malloc(s - start + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start != s)
	{
		res[i] = *start;
		i++;
		start++;
	}
	res[i] = 0;
	return (res);
}

void	*free_all(char **res)
{
	size_t	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_split_1space(const char *s, char c)
{
	char		**res;
	int			i;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		res[i] = ft_strndup(s, c);
		if (!res[i])
			return (free_all(res));
		i++;
		if (*s != c)
			while (*s && *s != c)
				s++;
		else if (*s == c)
			while (*s && *s == c)
				s++;
		if (*s && *s == c)
			s++;
	}
	res[i] = NULL;
	return (res);
}
