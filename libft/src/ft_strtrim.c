/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:47:08 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/07 15:34:49 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1) - 1;
	i = 0;
	while (in_set(s1[i], set))
		i++;
	if (i - 1 == len)
		return (ft_strdup(""));
	while (in_set(s1[len], set))
		len--;
	result = malloc(len - i + 2);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1 + i, len - i + 2);
	return (result);
}
