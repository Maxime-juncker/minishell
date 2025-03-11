/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:54:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 10:24:31 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	
int	has_open_heredoc(char *s)
{
	int		i;
	char	*tmp;

	tmp = ft_strnstr(s, "<<", ft_strlen(s));
	if (!tmp)
		return (0);
	i = 2;
	while (tmp[i])
	{
		if (!is_whitespace(tmp[i]))
			return (0);
		i++;
	}
	return (1);
}

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

static char *heredoc_delemiter(char *s, size_t *i)
{
	char	quote;
	size_t	start;

	start = *i;
	quote = 0;
	while (s[*i])
	{
		quote = toggle_quote(s[*i], quote);
		if (!is_whitespace(s[*i]) && !quote)
		{
			(*i)++;
			break;
		}
		(*i)++;
	}
	return (ft_substr(s, start, *i - start));
}

static int	add_str(t_list **lst, char *line, size_t *i)
{
	size_t	start;
	char	*tmp;
	t_list	*new;

	start = *i;
	while (line[*i] && line[*i] != '\'' && line[*i] != '\"')
	{
		(*i)++;
	}
	tmp = ft_substr(line, start, *i - start);
	if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	if (has_open_heredoc(tmp))
	{
		tmp = ft_strjoin_free(tmp, heredoc_delemiter(line, i), FREE1 | FREE2);
		if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
	}
	new = ft_lstnew(tmp);
	if (malloc_assert(new, __FILE__, __LINE__, __FUNCTION__))
		return (free(tmp), MALLOC_ERR);
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
			if (add_str(&lst, (char *)line, &i) == MALLOC_ERR)
				return (ft_lstclear(&lst, free), NULL);
		}
	}
	return (lst);
}
