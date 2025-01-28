/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:11:12 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/12 17:37:25 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_list(void *content, void (*del)(void *))
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		del(content);
		return (NULL);
	}
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;

	map = NULL;
	while (lst)
	{
		new = ft_create_list(f(lst->content), del);
		if (new == NULL)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, new);
		lst = lst->next;
	}
	return (map);
}
