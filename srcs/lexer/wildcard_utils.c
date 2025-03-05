/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:03:31 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 10:28:14 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

size_t	count_files(char *path)
{
	DIR				*dir;
	struct dirent	*infos;
	size_t			size;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	size = 0;
	infos = readdir(dir);
	while (infos)
	{
		size++;
		infos = readdir(dir);
	}
	closedir(dir);
	return (size);
}

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
		if (patern[*i][0] == -1)
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
