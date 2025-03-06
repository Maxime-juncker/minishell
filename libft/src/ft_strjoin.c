/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:56:58 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 17:35:38 by abidolet         ###   ########.fr       */
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

void	free_join(char *s1, char *s2, const int flags)
{
	if (flags & FREE1)
		free(s1);
	if (flags & FREE2)
		free(s2);
}

char	*ft_strjoin_free(char *s1, char *s2, const int flags)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (result = ft_strdup(s2), free_join(NULL, s2, flags), result);
	if (s2 == NULL)
		return (result = ft_strdup(s1), free_join(s1, NULL, flags), result);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
	{
		free_join(s1, (char *)s2, flags);
		return (NULL);
	}
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	free_join(s1, (char *)s2, flags);
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
		return (free(s1), NULL);
	ft_strlcpy(result, s1, len1 + 1);
	free(s1);
	result[len1] = c;
	result[len1 + 1] = '\0';
	return (result);
}
