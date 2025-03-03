/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:38 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/03 10:27:57 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			continue;
		}
		while (content[i] == ' ' && (*str_ref)[*len] == ' ')
			i++;
		*str_ref = ft_charjoin(*str_ref, content[i]);
		if (malloc_assert(*str_ref, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		i++;
		(*len)++;
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
