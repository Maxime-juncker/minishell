#include "minishell.h"

static char	*handle_dollar(char **str, int last_code, char **env)
{
	size_t	j;
	char	*var_name;
	char	*var_value;

	if (**str == '?')
		return ((*str)++, ft_itoa(last_code));
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
		if (!var_name)
			return (NULL);
		var_value = find_env_var(env, var_name, NULL);
		free(var_name);
		if (var_value)
			return (*str += j, ft_strdup(var_value));
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
		}
		else
		{
			result = ft_charjoin(result, *str);
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
		if (ft_lstadd_back(&process_lst, ft_lstnew(content)) == -1)
		{
			ft_lstclear(&process_lst, free);
			return (NULL);
		}
		lst = lst->next;
	}
	return (process_lst);
}
