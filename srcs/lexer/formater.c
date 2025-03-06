/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:22:25 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 17:36:23 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format(char *src, char *res, int i, int j)
{
	char	quote;

	quote = 0;
	while (src[++i])
	{
		quote = toggle_quote(src[i], quote);
		if (quote)
		{
			res[j] = src[i];
			j++;
			continue ;
		}
		if (res[j] - 1 == ' ' && src[i] == ' ')
		{
			continue ;
		}
		if (src[i] == '\t')
			res[j] = ' ';
		else
			res[j] = src[i];
		j++;
	}
	res[j] = '\0';
}

char	*format_spaces(char *src)
{
	char	*res;
	char	*tmp;
	int		i;
	int		j;

	if (src == NULL)
		return (NULL);
	res = ft_calloc(ft_strlen(src) + 1, 1);
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	i = -1;
	j = 0;
	format(src, res, i, j);
	free(src);
	tmp = ft_strdup(res);
	free(res);
	if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	return (tmp);
}
