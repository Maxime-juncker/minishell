#include "minishell.h"

int	is_literal(const char *str)
{
	if (str[0] == '\'')
		return (1);
	return (0);
}

char	*process_var(char *str, char **env)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			//* join var
			result = ft_strjoin_free(result, expand_env_var(ft_strdup(&str[i]), env, 0), FREE1 | FREE2);
			if (result == NULL)
				return (NULL);
			//* skip var in str
			i++;
			if (str[i] == '?')
			{
				i++;
			}
			else
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) //! peut poser pb si $9HOME par example
				{
					i++;
				}
			}
		}
		else
		{
			result = ft_charjoin(result, str[i]);
			if (result == NULL)
				return (NULL);
			i++;
		}

	}
	return (result);
}

int	only_quote(const char *str)
{
	return (str[0] == str[1] && (str[0] == '\'' || str[0] == '\"'));
}

t_list	*process_expanded_vars(const t_list *lst, char **env)
{
	t_list	*process_lst;
	char	*content;

	process_lst = NULL;
	content = NULL;
	while (lst)
	{
		if (is_literal(lst->content))
			content = ft_strdup(lst->content);
		else
			content = process_var(lst->content, env);
		if (!only_quote(content))
			ft_lstadd_back(&process_lst, ft_lstnew(content));
		lst = lst->next;
	}
	return (process_lst);
}
