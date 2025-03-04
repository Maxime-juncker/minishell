/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:38 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/04 09:00:06 by mjuncker         ###   ########.fr       */
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
	if (prompt[0] == ':' || prompt[0] == '!')
		prompt++;
	while (*prompt)
	{
		if (*prompt != ' ' || (*prompt >= 9 && *prompt <= 13))
			return (0);
		prompt++;
	}
	return (1);
}

static int	add_str(char *content, char **str_ref, int *len, int *i)
{
	if (add_space(&(*str_ref)[*len], content[*i]) == 1)
	{
		*str_ref = ft_charjoin(*str_ref, ' ');
		if (malloc_assert(*str_ref, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		(*len)++;
		return (0);
	}
	while (*str_ref && content[*i] == ' ' && (*str_ref)[*len - 1] == ' ')
		(*i)++;
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

	if (ignore_prompt(content))
		return (0);
	quote = 0;
	i = 0;
	while (content[i])
	{
		quote = toggle_quote(content[i], quote);
		if (quote)
		{
			*str_ref = ft_charjoin(*str_ref, content[i]);
			if (malloc_assert(*str_ref, __FILE__, __LINE__, __FUNCTION__))
				return (MALLOC_ERR);
			(*len)++;
			i++;
			continue ;
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
	return (str);
}
