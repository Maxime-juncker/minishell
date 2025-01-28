/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:57:33 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/20 15:31:15 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// dsize include space for the null terminator
size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	len;

	if (src == NULL)
		return (0);
	len = ft_strlen(dst);
	i = len;
	if (dsize < len || dsize == 0)
		return (dsize + ft_strlen(src));
	while (i < dsize - 1 && src[i - len])
	{
		dst[i] = src[i - len];
		i++;
	}
	dst[i] = '\0';
	return (len + ft_strlen(src));
}
