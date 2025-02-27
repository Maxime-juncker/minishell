/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:40 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/27 16:17:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar(char **str, int last_code, char **env)
{
	size_t	j;
	char	*var_name;
	char	*var_value;

	if (**str == '?')
		return ((*str)++, ft_itoa(last_code % 256));
	else if (**str == '0')
		return ((*str)++, ft_strdup("minishell"));
	else if (ft_isdigit(**str))
		return ((*str)++, ft_strdup(""));
	else if (ft_isalnum(**str) || **str == '_')
	{
		j = 0;
		while ((*str)[j] && (ft_isalnum((*str)[j]) || (*str)[j] == '_'))
			j++;
		var_name = ft_substr(*str, 0, j);
		if (malloc_assert(var_name, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
		var_value = find_env_var(env, var_name, NULL);
		free(var_name);
		if (var_value)
			return (*str += j, var_value);
		return (*str += j, ft_strdup(""));
	}
	return (ft_strdup("$"));
}

static char	*process_var(char *str, char **env, int last_code)
{
	char	*result;

	result = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			result = ft_strjoin_free(result,
					handle_dollar(&str, last_code, env), FREE1 | FREE2);
			if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
				return (NULL);
		}
		else
		{
			result = ft_charjoin(result, *str);
			if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
				return (NULL);
			str++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

t_list	*process_expanded_vars(const t_list *lst, char **env, int last_code)
{
	t_list	*process_lst;
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
			content = process_var(str_content, env, last_code);
		if (!content)
			return (NULL);
		if (ft_lstadd_back(&process_lst, ft_lstnew(content)) == -1)
			return (malloc_assert(NULL, __FILE__,
					__LINE__, __FUNCTION__), NULL);
		lst = lst->next;
	}
	return (process_lst);
}
