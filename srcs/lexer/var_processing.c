#include "minishell.h"

static int	add_new_str(char **process_str, char *new_str, int is_str_literal, char **env)
{
	int		i;
	char	*expanded_var;

	i = 0;
	expanded_var = NULL;
	while (new_str[i])
	{
		if (new_str[i] == '$' && !is_str_literal)
		{
			expanded_var = expand_env_var(ft_strdup(&new_str[i]), env, 0);
			if (!expanded_var)
				return (MALLOC_ERR);
			*process_str = ft_strjoin_free(*process_str, expanded_var, 1, 1);
			if (!*process_str)
			{
				free(expanded_var);
				return (MALLOC_ERR);
			}
			if (new_str[i + 1] == ' ')
				i++;
			while (ft_isalnum(new_str[i + 1]) || new_str[i + 1] == '_' || new_str[i + 1] == '?')
				i++;
		}
		else
		{
			*process_str = ft_charjoin(*process_str, new_str[i]);
			if (!*process_str)
			{
				if (expanded_var)
					free(expanded_var);
				if (process_str)
					free(*process_str);
				return (MALLOC_ERR);
			}
		}
		i++;
	}
	return (0);
}

static int	setup_str(char **str, const t_list *lst)
{
	int		is_str_literal;

	if ((*str)[0] == '\'')
	{
		is_str_literal = 1;
		*str = ft_strtrim(*str, "\'");
		if (!*str)
			return (MALLOC_ERR);
	}
	else
	{
		is_str_literal = 0;
		*str = ft_strtrim(*str, "\"");
		if (!*str)
			return (MALLOC_ERR);
	}
	return (is_str_literal);
}

char	*process_expanded_vars(const t_list *lst, char **env)
{
	char	*str;
	char	*process_str;
	int		is_str_literal;

	process_str = NULL;
	while (lst)
	{
		str = ((char *)lst->content);
		is_str_literal = setup_str(&str, lst);
		if (is_str_literal == MALLOC_ERR)
			return (NULL);
		add_new_str(&process_str, str, is_str_literal, env);
		free(str);
		lst = lst->next;
	}
	return (process_str);
}
