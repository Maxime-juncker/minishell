/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:37:15 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/13 15:46:56 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL)
		return (-1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		if (ft_lstlast(*lst))
			ft_lstlast(*lst)->next = new;
	}
	return (0);
}
