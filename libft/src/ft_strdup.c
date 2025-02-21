/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:56:43 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 11:24:48 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	copy = malloc(len);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s, len);
	return (copy);
}

char	*ft_strndup(const char *s, char c)
{
	const char	*start;
	char		*res;
	size_t		i;

	start = s;
	while (*s && *s != c)
		s++;
	res = malloc(s - start + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start != s)
		res[i++] = *start++;
	return (res[i] = 0, res);
}

char	*ft_strdup_except_char(char *s, char c)
{
	char	*copy;
	int		i;

	if (!s)
		return (NULL);
	copy = malloc(ft_strlen(s));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
			copy[i++] = *s;
		s++;
	}
	copy[i] = 0;
	free(s);
	return (copy);
}
