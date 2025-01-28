/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:56:01 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/08 13:50:03 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstchr_n(t_list *lst, int n)
{
	int	i;

	if (lst == NULL)
		return (-1);
	i = 0;
	while (lst)
	{
		if (ft_atoi(lst->content) == n)
		{
			return (i);
		}
		lst = lst->next;
		i++;
	}
	return (-1);
}

t_list	*ft_lstchr(t_list *lst, void *content)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->content == content)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}
