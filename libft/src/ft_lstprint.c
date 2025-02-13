/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:23:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/09 11:33:35 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(const char *msg, t_list *lst)
{
	if (lst == NULL)
		return ;
	ft_printf("%s [", msg);
	while (lst->next)
	{
		ft_printf("%s => ", lst->content);
		lst = lst->next;
	}
	ft_printf("%s]\n", lst->content);
}
