/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:59:47 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/07 15:32:48 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s) || len == 0)
		return (0);
	while (s[i + start] && i < len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	sub = malloc(get_len(s, start, len) + 1);
	if (sub == NULL)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
	{
		sub[0] = '\0';
		return (sub);
	}
	i = 0;
	while (i < len && s[i + start])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
