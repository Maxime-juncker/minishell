/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:49:20 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/02 19:13:22 by mjuncker         ###   ########.fr       */
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
