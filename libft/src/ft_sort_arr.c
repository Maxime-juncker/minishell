/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:40:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 10:30:00 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	arrlen(void **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int	strcmp_lower(char *s1, char *s2)
{
	int	i;

	if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (ft_tolower(s1[i]) != ft_tolower(s2[i]))
			return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
		i++;
	}
	if (ft_tolower(s1[i]) || ft_tolower(s2[i]))
		return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
	return (0);
}

void	ft_sort_normalized(char **arr)
{
	int		i;
	int		diff;
	char	*temp;
	int		size;

	diff = 1;
	size = arrlen((void **)arr);
	while (diff)
	{
		i = 0;
		diff = 0;
		while (i < (size - 1))
		{
			if (strcmp_lower(arr[i], arr[i + 1]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				diff = 1;
			}
			i++;
		}
	}
}
