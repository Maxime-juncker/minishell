/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:58:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/10 11:52:06 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strclen(const char *s, char c)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}
