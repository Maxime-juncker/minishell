/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_patern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:01:51 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 10:28:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_arr(char **patern)
{
	char	**new_patern;
	int		i;

	if (patern == NULL)
		return (NULL);
	i = 0;
	while (patern[i])
		i++;
	new_patern = ft_calloc(i + 1, sizeof(char *));
	if (malloc_assert(new_patern, __FILE__, __LINE__, __FUNCTION__))
		return (cleanup_arr((void **)patern), NULL);
	i = 0;
	while (patern[i])
	{
		new_patern[i] = patern[i];
		i++;
	}
	new_patern[i] = NULL;
	free(patern);
	return (new_patern);
}

static int	add_part(char **line, char **patern, int *j, char *quote)
{
	int		i;
	char	*sub;

	i = 0;
	while ((*line)[i] && (((*line)[i] != ' ' && (*line)[i] != '*') || *quote))
	{
		*quote = toggle_quote((*line)[i], *quote);
		i++;
	}
	sub = ft_substr(*line, 0, i);
	patern[*j] = remove_quotes_pair(sub);
	free(sub);
	if (malloc_assert(patern[*j], __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	(*j)++;
	*line += i;
	return (0);
}

static int	add_patern(char **line, char **patern, int *j)
{
	char	quote;

	quote = 0;
	if (*line[0] != '*')
	{
		if (add_part(line, patern, j, &quote) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		if (*j == 0 || patern[*j - 1][0] != -1)
		{
			patern[*j] = malloc(2);
			patern[(*j)][0] = -1;
			patern[(*j)][1] = 0;
			if (malloc_assert(patern[(*j)++], __FILE__, __LINE__, __FUNCTION__))
				return (MALLOC_ERR);
			while (*line[0] == '*')
				(*line)++;
		}
	}
	return (0);
}

char	**new_patern(char *line)
{
	char	**patern;
	int		j;

	patern = ft_calloc(ft_strlen(line) + 1, sizeof(char *));
	if (malloc_assert(patern, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	j = 0;
	while (*line && *line != ' ')
	{
		if (add_patern(&line, patern, &j) == MALLOC_ERR)
		{
			cleanup_arr((void **)patern);
			return (NULL);
		}
	}
	patern[j] = NULL;
	return (realloc_arr(patern));
}
