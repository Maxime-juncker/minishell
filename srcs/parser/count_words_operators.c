/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:38:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/16 20:58:20 by abidolet         ###   ########.fr       */
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

int	count_words_operators(char *s)
{
	int		count;
	char	in_quote;

	count = 0;
	in_quote = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (!*s)
			break ;
		if (*s == '(' || is_operator(s))
			handle_operator(&s, &count);
		else
		{
			count++;
			while (*s && *s != ' ' && *s != '(' && !is_operator(s))
			{
				if (*s == '\'' || *s == '\"')
					in_quote = toggle_quote(*s, in_quote);
				s++;
			}
		}
	}
	return (count);
}
