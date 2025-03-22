/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_processing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:20:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/22 17:54:54 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*supp_spaces(char *s)
{
	char	*res;
	int		i;

	res = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	res[0] = '"';
	i = 1;
	while (is_whitespace(*s))
		s++;
	while (*s)
	{
		res[i++] = *s++;
		if (is_whitespace(*s))
		{
			while (is_whitespace(*s))
				s++;
			if (*s)
				res[i++] = ' ';
		}
	}
	res[i] = '"';
	res[i + 1] = 0;
	return (ft_strdup(res));
}

static char	*update_env_var(char *var_value, int in_quote)
{
	char	*first;
	char	*second;

	if (!ft_strchr(var_value, ' '))
		return (var_value);
	first = ft_strndup(var_value, ' ');
	if (malloc_assert(first, __FILE__, __LINE__, __FUNCTION__))
		return (free(var_value), NULL);
	first = ft_charjoin(first, ' ');
	if (malloc_assert(first, __FILE__, __LINE__, __FUNCTION__))
		return (free(var_value), NULL);
	if (!in_quote)
		second = supp_spaces(ft_strchr(var_value, ' ') + 1);
	else
		second = ft_strdup(ft_strchr(var_value, ' ') + 1);
	free(var_value);
	if (malloc_assert(second, __FILE__, __LINE__, __FUNCTION__))
		return (free(first), NULL);
	return (ft_strjoin_free(first, second, FREE1 | FREE2));
}

static char	*handle_dollar(char **str, int last_code, char **env, int in_quote)
{
	char	*start;
	char	*var_name;

	(*str)++;
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
		start = find_env_var(env, var_name, NULL);
		free(var_name);
		if (start)
			return (update_env_var(start, in_quote));
		return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}

static char	*add_heredoc_delemiter(char **s)
{
	char	quote;
	int		i;
	char	*sub;

	quote = 0;
	i = 2;
	while ((*s)[i])
	{
		quote = toggle_quote((*s)[i], quote);
		if (!is_whitespace((*s)[i]) && !quote)
		{
			i++;
			break ;
		}
		i++;
	}
	sub = ft_substr(*s, 0, i);
	*s += i;
	return (sub);
}

int	process(char **str, char **result, int last_code, char **env)
{
	char		*tmp;
	static int	in_quote = 0;

	if (*str[0] == '<' && *(str[0] + 1) == '<')
	{
		tmp = add_heredoc_delemiter(str);
		if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		*result = ft_strjoin_free(*result, tmp, FREE1 | FREE2);
	}
	else if (*str[0] == '$')
	{
		tmp = handle_dollar(str, last_code, env, in_quote);
		if (malloc_assert(tmp, __FILE__, __LINE__, __FUNCTION__))
			return (MALLOC_ERR);
		*result = ft_strjoin_free(*result, tmp, FREE1 | FREE2);
	}
	else
	{
		if (**str == '"')
			in_quote = !in_quote;
		*result = ft_charjoin(*result, *str[0]);
		(*str)++;
	}
	return (0);
}
