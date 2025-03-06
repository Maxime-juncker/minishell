/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:40 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 16:37:27 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar(char **str, int last_code, char **env)
{
	char	*start;
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
		start = *str;
		while (*str && (ft_isalnum(**str) || **str == '_'))
			(*str)++;
		var_name = ft_substr(start, 0, *str - start);
		if (malloc_assert(var_name, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
		var_value = find_env_var(env, var_name, NULL);
		free(var_name);
		if (var_value)
			return (var_value);
		return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}

char	*process_var(char *str, char **env, int last_code, t_list *next)
{
	char	*result;
	char	*tmp;

	result = NULL;
	while (*str)
	{
		if (*str == '$' && str[1] == '\0' && next)
			return (result);
		if (*str == '$')
		{
			str++;
			tmp = handle_dollar(&str, last_code, env);
			if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
				return (free(result), NULL);
			result = ft_strjoin_free(result, tmp, FREE1 | FREE2);
		}
		else
		{
			result = ft_charjoin(result, *str);
			str++;
		}
		if (malloc_assert(result, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
	}
	return (result);
}

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
