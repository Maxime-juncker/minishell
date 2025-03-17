/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:40 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/17 10:21:01 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*process_expanded_vars(const t_list *lst, char **env, int last_code)
{
	t_list	*process_lst;
	t_list	*tmp;
	char	*content;
	char	*str_content;

	process_lst = NULL;
	content = NULL;
	while (lst)
	{
		str_content = (char *)lst->content;
		if (str_content[0] == '\'')
			content = ft_strdup(str_content);
		else
			content = process_var(str_content, env, last_code, lst->next);
		if (malloc_assert(content, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
		tmp = ft_lstnew(content);
		if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
			return (free(content), NULL);
		ft_lstadd_back(&process_lst, tmp);
		lst = lst->next;
	}
	return (process_lst);
}
