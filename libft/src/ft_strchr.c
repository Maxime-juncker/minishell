/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:53:40 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/10 12:04:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c % 256)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c % 256)
		return ((char *)(s + i));
	return (NULL);
}

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c % 256)
			return (i);
		i++;
	}
	if (s[i] == c % 256)
		return (i);
	return (-1);
}
