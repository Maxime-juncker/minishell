/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:38 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 17:23:34 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_space(char *dest, char c)
{
	if (!dest)
		return (0);
	if (is_symbol(c)
		&& !is_symbol(*(dest - 1))
		&& *(dest - 1) != ' ')
		return (1);
	if (!is_symbol(c)
		&& is_symbol(*(dest - 1))
		&& c != ' ')
		return (1);
	return (0);
}

int	ignore_prompt(char *prompt)
{
	if (prompt == NULL)
		return (1);
	if (prompt[0] == ':' || prompt[0] == '!')
		prompt++;
	while (*prompt)
	{
		if (!is_whitespace(*prompt))
			return (0);
		prompt++;
	}
	return (1);
}

static int	add_str(char *content, char **str_ref, int *len, int *i)
{
	if (*str_ref && content[*i] && is_whitespace(content[*i])
		&& is_whitespace((*str_ref)[*len - 1]))
	{
		(*i)++;
		return (0);
	}
	if (*str_ref && add_space(&(*str_ref)[*len], content[*i]) == 1)
	{
		*str_ref = ft_charjoin(*str_ref, ' ');
		if (malloc_assert(*str_ref, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		(*len)++;
		return (0);
	}
	*str_ref = ft_charjoin(*str_ref, content[*i]);
	if (malloc_assert(*str_ref, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	(*i)++;
	(*len)++;
	return (0);
}

static int	join_loop(char *content, char **str_ref, int *len)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (content[i])
	{
		quote = content[0];
		if (quote == '\'' || quote == '\"')
		{
			*str_ref = ft_strjoin_free(*str_ref, content, FREE1);
			if (malloc_assert(*str_ref, __FILE__, __LINE__, __FUNCTION__))
				return (MALLOC_ERR);
			*len = ft_strlen(*str_ref);
			return (0);
		}
		if (add_str(content, str_ref, len, &i) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (0);
}

char	*join_lst(t_list *lst)
{
	char	*str;
	int		len;

	str = NULL;
	len = 0;
	while (lst)
	{
		if (join_loop(lst->content, &str, &len) == MALLOC_ERR)
			return (NULL);
		lst = lst->next;
	}
	return (format_spaces(str));
}
