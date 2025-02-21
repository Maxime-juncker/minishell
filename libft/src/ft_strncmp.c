/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:58:50 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 13:25:18 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	return (0);
}

int	in(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strscmp(const char *s1, const char *s2, char *s)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (cs1[i] && !in(cs1[i], s))
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] || s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
