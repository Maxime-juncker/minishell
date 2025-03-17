/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:38:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/17 09:14:45 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_operator(char **s, int *count)
{
	static int	paren_count = 0;

	if (**s == '(')
	{
		paren_count++;
		*count += 1;
		**s += 1;
		while (**s && (**s != ')' || paren_count > 1))
		{
			if (**s == '(')
				paren_count++;
			else if (**s == ')')
				paren_count--;
			**s += 1;
		}
		if (**s == ')')
			**s += 1;
	}
	else
	{
		*count += 1;
		**s += 2;
	}
}

int	count_words_operators(const char *s)
{
	int		count;
	char	in_quote;
	char	*temp;

	temp = (char *)s;
	count = 0;
	in_quote = 0;
	while (*temp)
	{
		while (*temp == ' ')
			temp++;
		if (!*temp)
			break ;
		if (*temp == '(' || is_operator(temp))
			handle_operator(&temp, &count);
		else
		{
			count++;
			while (*temp && *temp != ' ' && *temp != '(' && !is_operator(temp))
			{
				if (*temp == '\'' || *temp == '\"')
					in_quote = toggle_quote(*temp, in_quote);
				temp++;
			}
		}
	}
	return (count);
}
