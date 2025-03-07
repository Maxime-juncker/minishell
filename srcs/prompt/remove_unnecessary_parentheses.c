/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_unnecessary_parentheses.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:31:31 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/07 14:34:26 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_parenthesis_back(char *s, int i)
{
	while (i != 0 && is_whitespace(s[i]))
		i--;
	if (s[i] == ')')
	{
		s[i] = ' ';
		i--;
		while (i != 0 && s[i] != '(')
			i--;
		if (s[i] == '(')
			s[i] = ' ';
	}
}

static void	check_parenthesis_front(char *s, int *i)
{
	int	j;

	while (is_whitespace(s[*i]))
		*i += 1;
	if (s[*i] == '(')
	{
		s[*i] = ' ';
		j = *i + 1;
		while (s[j] && s[j] != ')')
			j++;
		if (s[j])
			s[j] = ' ';
	}
}

void	remove_unnecessary_parentheses(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == '|' && s[i + 1] != '|')
		{
			check_parenthesis_back(s, i - 1);
			i++;
			check_parenthesis_front(s, &i);
		}
		else if (s[i] == '|' && s[i + 1])
			i += 2;
		else
			i++;
	}
}
