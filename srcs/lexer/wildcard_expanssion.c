/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expanssion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:50:51 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/24 09:26:00 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	include_file(char *filename, char **patern)
{
	int		i;
	char	*tmp;
	char	*new_tmp;

	tmp = filename;
	i = 0;
	if (patern[i][0] != -1)
	{
		new_tmp = ft_strnstr(tmp, patern[i], ft_strlen(tmp));
		if (tmp != new_tmp)
			return (0);
		i++;
	}
	if (patern_valid(tmp, patern, &i) == 0)
		return (0);
	if (patern[i][0] == -1)
		return (1);
	tmp = ft_strrstr(tmp, patern[i]);
	if (tmp == NULL)
		return (0);
	if (ft_strlen(tmp) == ft_strlen(patern[i]))
		return (1);
	return (0);
}

int	add_file(DIR *dir, struct dirent **infos, char **expanded)
{
	int	i;

	i = 0;
	(void)dir;
	while (expanded[i])
		i++;
	expanded[i] = ft_strdup((*infos)->d_name);
	if (malloc_assert(expanded[i], __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	return (0);
}

char	*add_files(char *line, DIR *dir, char **patern)
{
	struct dirent	*infos;
	char			**expanded;

	expanded = ft_calloc(count_files(".") + 1, sizeof(char *));
	if (malloc_assert(expanded, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	infos = readdir(dir);
	while (infos)
	{
		if (infos->d_name[0] != '.' || patern[0][0] == '.')
		{
			if (include_file(infos->d_name, patern))
			{
				if (add_file(dir, &infos, expanded) == MALLOC_ERR)
					return (cleanup_arr((void **)patern), NULL);
			}
		}
		infos = readdir(dir);
	}
	if (expanded[0] == NULL)
		return (cleanup_arr((void **)expanded), ft_strdup(line));
	ft_sort_normalized(expanded);
	return (format_wildcard(expanded));
}

int	expand_necessary(char **patern)
{
	int	i;

	i = 0;
	while (patern[i])
	{
		if (patern[i][0] == -1)
			return (1);
		i++;
	}
	return (0);
}

char	*expand_wildcard(char *line)
{
	DIR		*dir;
	char	**patern;
	char	*expanded;

	if (ft_strchr(line, '*') == NULL)
		return (ft_strdup(line));
	dir = opendir(".");
	if (!dir)
		return (perror("can't open dir"), NULL);
	patern = new_patern(line);
	if (patern == NULL)
		return (closedir(dir), NULL);
	if (!expand_necessary(patern))
		return (ft_strdup(line));
	expanded = add_files(line, dir, patern);
	closedir(dir);
	cleanup_arr((void **)patern);
	return (expanded);
}
