/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:38:55 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/07 10:03:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_atos(char **arr, char separator)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (arr[i])
	{
		result = ft_strjoin_free(result, arr[i], FREE1);
		if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
		if (arr[i + 1])
		{
			result = ft_charjoin(result, separator);
			if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
				return (NULL);
		}
		i++;
	}
	return (result);
}
