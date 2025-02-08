#include "minishell.h"

static char	*remove_quotes(const char *line)
{
	char	*new_line;
	int		i;
	char	quote_type;

	new_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 1;
	quote_type = line[0];
	if (line[1] == quote_type)
	{
		new_line[0] = '\0';
		return (new_line);
	}
	new_line[0] = quote_type;
	while (line[i])
	{
		new_line[i] = line[i];
		if (line[i] == quote_type)
		{
			i++;
			break ;
		}
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

static t_list	*process_quotes(const char *line)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	t_list	*lst;
	int		line_len;
	char	buff[1000];

	i = 0;
	j = 0;
	lst = NULL;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			tmp = remove_quotes(&line[i]);
			if (tmp[0] != '\0')
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(tmp)));
				i += ft_strlen(tmp);
			}
			else
				i += 2;
			free(tmp);
		}
		else
		{
			j = 0;
			while (line[i] && !(line[i] == '\'' || line[i] == '\"'))
			{
				buff[j] = line[i];
				i++;
				j++;
			}
			buff[j] = 0;
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buff)));
		}
	}
	return (lst);
}

static char	*process_expanded_vars(const t_list *lst)
{
	t_list	*expanded;
	int		i;
	char	*str;
	char	*process_str;
	int		is_str_literal;
	char	*expanded_var;

	process_str = NULL;
	while (lst)
	{
		i = 0;
		str = ((char *)lst->content);
		if (str[0] == '\'')
		{
			is_str_literal = 1;
			str = ft_strtrim(str, "\'");
		}
		else
		{
			is_str_literal = 0;
			str = ft_strtrim(str, "\"");
		}
		if (!str)
			return (NULL);
		while (str[i])
		{
			if (str[i] == '$' && !is_str_literal)
			{
				expanded_var = expand_env_var(ft_strdup(&str[i]), __environ, 0);
				process_str = ft_strjoin(process_str, expanded_var);
				i++;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
			}
			else
			{
				process_str = ft_charjoin(process_str, str[i]);
				i++;
			}
		}
		lst = lst->next;
	}
	return (process_str);
}

char	*process_line(const char *cmd_line)
{
	t_list	*process_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	process_lst = process_quotes(cmd_line);
	process_str = process_expanded_vars(process_lst);
	return (process_str);
}
