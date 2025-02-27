/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:49:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 09:56:17 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strncmp(little, "\0", 1) == 0)
		return ((char *)(big));
	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && i + j < len && little[j])
				j++;
			if (j == ft_strlen(little))
				return ((char *)(big + i));
			j = 0;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strrstr(const char *big, const char *little)
{
	int	i;
	int	j;
	int	len;

	if (ft_strncmp(little, "\0", 1) == 0)
		return ((char *)(big));
	i = ft_strlen(big);
	len = ft_strlen(little);
	j = 0;
	while (i > 0)
	{
		if (big[i - 1] == little[len - 1])
		{
			while (i - j - 1 >= 0 && len - j - 1 >= 0 &&
				big[i - j - 1] == little[len - j - 1])
			 	j++;
			if (j == len)
				return ((char *)(big + i - len));
			j = 0;
		}
		i--;
	}
	return (NULL);
}
