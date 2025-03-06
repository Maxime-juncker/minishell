/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:23:19 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 15:19:13 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_wildcard(char *line)
{
	if (line[0] == '\'' || line[0] == '\"')
		return (ft_strdup(line));
	return (expand_wildcard(line));
}

char	*get_wildcard(t_list *lst)
{
	char	*result;

	result = NULL;
	while (lst)
	{
		result = ft_strjoin_free(result,
				add_wildcard((char *)lst->content), FREE1 | FREE2);
		if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
		if (lst->next)
		{
			result = ft_charjoin(result, ' ');
			if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
				return (NULL);
		}
		lst = lst->next;
	}
	return (result);
}

char	*process_wildcard(char *line)
{
	t_list	*lst;
	char	*result;

	if (ignore_prompt(line))
		return (line);
	if (!line)
		return (NULL);
	lst = split_line(line);
	free(line);
	if (malloc_assert(lst, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	result = NULL;
	result = get_wildcard(lst);
	ft_lstclear(&lst, free);
	return (result);
}
