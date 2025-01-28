/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:23:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/08 13:36:46 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	ft_printf("[");
	while (lst->next)
	{
		ft_printf("%s => ", lst->content);
		lst = lst->next;
	}
	ft_printf("%s]\n", lst->content);
}
