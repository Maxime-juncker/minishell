/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:56:58 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/10 11:02:42 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	return (result);
}

char	*ft_strjoin_free(char *s1, char const *s2, const int free1, const int free2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	if (free1)
		free(s1);
	if (free2)
		free((char *)s2);
	return (result);
}

char	*ft_charjoin(char *s1, char const c)
{
	char	*result;
	size_t	len1;

	if (!s1)
	{
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = c;
		result[1] = 0;
		return (result);
	}
	len1 = ft_strlen(s1);
	result = malloc(len1 + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	free(s1);
	result[len1] = c;
	result[len1 + 1] = '\0';
	return (result);
}
