/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:04:53 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/07 10:08:43 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pad(char *s, char c)
{
	char	*res;
	int		i;

	res = ft_calloc(ft_strlen(s) + 3, sizeof(char));
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	res[0] = c;
	i = 0;
	while (s[i])
	{
		res[i + 1] = s[i];
		i++;
	}
	res[i + 1] = c;
	res[i + 2] = '\0';
	return (res);
}
