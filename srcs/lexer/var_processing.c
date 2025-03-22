/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:20:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/22 17:56:18 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_var(char *str, char **env, int last_code, t_list *next)
{
	char	*result;

	result = NULL;
	if (*str == 0)
		return (ft_strdup(""));
	while (*str)
	{
		if (*str == '$' && str[1] == '\0' && next)
			return (result);
		if (process(&str, &result, last_code, env) == MALLOC_ERR)
			return (free(result), NULL);
		if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
	}
	return (result);
}

t_list	*process_expanded_vars(const t_list *lst, char **env,
	int last_code)
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
