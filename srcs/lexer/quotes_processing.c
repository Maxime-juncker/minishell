/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:54:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 16:51:25 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_quotes(t_list **lst, const char *line, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != line[start])
	{
		(*i)++;
	}
	(*i)++;
	if (ft_lstadd_back(lst, ft_lstnew(ft_substr(line, start, *i - start)))
		== -1)
		return (MALLOC_ERR);
	return (0);
}

char	*remove_spaces(char *str)
{
	char	*buff;
	char	*new_str;
	int		i;
	char	last;

	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (malloc_assert(buff, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	i = 0;
	last = 0;
	while (*str)
	{
		if (is_whitespace(*str) && is_whitespace(last))
		{
			last = *str;
			str++;
			continue ;
		}
		buff[i] = *str;
		last = *str;
		i++;
		str++;
	}
	new_str = ft_strdup(buff);
	return (free(buff), new_str);
}

static int	add_str(t_list **lst, const char *line, size_t *i)
{
	size_t	start;
	char	*temp;
	t_list	*new;

	start = *i;
	while (line[*i] && line[*i] != '\'' && line[*i] != '\"')
	{
		(*i)++;
	}
	temp = ft_substr(line, start, *i - start);
	temp = remove_spaces(temp);
	if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	new = ft_lstnew(temp);
	if (malloc_assert(new, __FILE__, __LINE__, __FUNCTION__))
		return (free(temp), MALLOC_ERR);
	ft_lstadd_back(lst, new);
	return (0);
}

t_list	*process_quotes(const char *line)
{
	size_t	i;
	t_list	*lst;
	size_t	line_len;

	i = 0;
	lst = NULL;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (add_quotes(&lst, line, &i) == MALLOC_ERR)
				return (ft_lstclear(&lst, free), NULL);
		}
		else
		{
			if (add_str(&lst, line, &i) == MALLOC_ERR)
				return (ft_lstclear(&lst, free), NULL);
		}
	}
	return (lst);
}
