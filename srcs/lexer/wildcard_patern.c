/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_patern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:01:51 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/02 11:02:28 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_patern(char **tmp, char *patern)
{
	char	*new_tmp;

	new_tmp = ft_strnstr(*tmp, patern, ft_strlen(*tmp));
	if (new_tmp == NULL)
		return (1);
	while (*tmp == new_tmp)
	{
		*tmp += ft_strlen(patern);
		new_tmp = ft_strnstr(*tmp, patern, ft_strlen(*tmp));
	}
	return (0);
}

int	patern_valid(char *tmp, char **patern, int *i)
{
	while (patern[*i])
	{
		if (patern[*i + 1] == NULL)
			break ;
		if (patern[*i][0] == '*')
		{
			if (patern[*i + 2] == NULL)
			{
				(*i)++;
				break ;
			}
			tmp = ft_strnstr(tmp, patern[*i + 1], ft_strlen(tmp));
			if (tmp == NULL)
				return (0);
			(*i)++;
			continue ;
		}
		if (check_patern(&tmp, patern[*i]) == 1)
			return (0);
		(*i)++;
	}
	return (1);
}

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

static int	add_patern(char **line, char **patern, int *j)
{
	int	i;

	if (*line[0] != '*')
	{
		i = 0;
		while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '*')
			i++;
		patern[*j] = ft_substr(*line, 0, i);
		if (malloc_assert(patern[*j], __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		(*j)++;
		*line += i;
	}
	else
	{
		if (*j == 0 || patern[*j - 1][0] != '*')
		{
			patern[*j] = ft_strdup("*");
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
