/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:54:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 15:32:34 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_quotes(t_list **lst, const char *line, size_t *i)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
		return (ft_lstclear(lst, free), MALLOC_ERR);
	if (tmp[0] != '\0')
	{
		if (ft_lstadd_back(lst, ft_lstnew(ft_strdup(tmp))) == -1)
			return (malloc_assert(NULL, __FILE__, __LINE__, __FUNCTION__), MALLOC_ERR);
		*i += ft_strlen(tmp);
	}
	else
		*i += 2;
	free(tmp);
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
		if (*str == ' ' && last == ' ')
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
	char	*tmp;
	char	*new_str;
	size_t	j;

	tmp = ft_calloc(get_str_len(&line[*i]) + 1, sizeof(char));
	if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	j = 0;
	while (line[*i] && !(line[*i] == '\'' || line[*i] == '\"'))
	{
		tmp[j] = line[*i];
		(*i)++;
		j++;
	}
	tmp[j] = '\0';
	new_str = remove_spaces(tmp);
	free(tmp);
	if (malloc_assert(new_str, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	if (ft_lstadd_back(lst, ft_lstnew(ft_strdup(new_str))) == -1)
		return (free(new_str), MALLOC_ERR);
	free(new_str);
	return (0);
}

t_list	*process_quotes(const char *line)
{
	size_t		i;
	t_list		*lst;
	size_t		line_len;

	i = 0;
	lst = NULL;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (add_quotes(&lst, &line[i], &i) == MALLOC_ERR)
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
