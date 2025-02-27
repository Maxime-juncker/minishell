/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:29 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 13:04:44 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_tmp(char *tmp, t_list **lst)
{
	if (tmp)
	{
		if (ft_lstadd_back(lst, ft_lstnew(ft_strdup(tmp))) == -1)
		{
			ft_lstclear(lst, free);
			free(tmp);
			return (malloc_assert(NULL, INFO), MALLOC_ERR);
		}
		free(tmp);
	}
	return (0);
}

static int	add_lines(char *line, t_list **lst, char **tmp)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (line[i])
	{
		if (quote == 0 && line[i] == ' ')
		{
			if (add_tmp(*tmp, lst) == MALLOC_ERR)
				return (MALLOC_ERR);
			*tmp = NULL;
			i++;
			continue ;
		}
		quote = toggle_quote(line[i], quote);
		*tmp = ft_charjoin(*tmp, line[i]);
		if (malloc_assert(*tmp, INFO))
			return (MALLOC_ERR);
		i++;
	}
	return (0);
}

t_list	*split_line(char *line)
{
	t_list	*lst;
	char	*tmp;

	lst = NULL;
	tmp = NULL;
	add_lines(line, &lst, &tmp);
	if (add_tmp(tmp, &lst) == MALLOC_ERR)
		return (NULL);
	return (lst);
}
