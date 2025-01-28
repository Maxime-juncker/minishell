/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:42:45 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/11 18:10:40 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_split(char const *s, char c)
{
	size_t		i;
	size_t		n;
	short int	new;

	if (!s)
		return (0);
	n = 0;
	i = 0;
	new = 1;
	while (s[i])
	{
		if (s[i] != c && new)
		{
			n++;
			new = 0;
		}
		else if (s[i] == c)
			new = 1;
		i++;
	}
	return (n);
}

static size_t	get_split_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static void	cleanup(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	wrong_split(char **split, size_t y)
{
	if (split[y] == NULL)
	{
		cleanup(split, y);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	y;

	if (!s)
		return (NULL);
	y = 0;
	result = malloc((get_nb_split(s, c) + 1) * sizeof(char *));
	if (!result || !s)
		return (NULL);
	while (s[0])
	{
		while (s[0] == c && s[0])
			s++;
		if (get_split_len(s, c) == 0)
			break ;
		result[y] = malloc(get_split_len(s, c) + 1);
		if (wrong_split(result, y))
			return (NULL);
		i = 0;
		while (s[0] != c && s[0])
			result[y][i++] = s++[0];
		result[y++][i] = '\0';
	}
	return ((result[y] = NULL), result);
}
