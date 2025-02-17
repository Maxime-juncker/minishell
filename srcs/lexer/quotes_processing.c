#include "minishell.h"

static size_t	get_str_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	return (i);
}

char	*remove_quotes(const char *line)
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
		i++;
		if (line[i - 1] == quote_type)
			break ;
	}
	new_line[i] = '\0';
	return (new_line);
}

static int	add_quotes(t_list **lst, const char *line, size_t *i)
{
	char	*tmp;
	int		lst_size;

	// tmp = remove_quotes(line);
	tmp = ft_strdup(line);
	if (!tmp)
	{
		ft_lstclear(lst, free);
		return (MALLOC_ERR);
	}
	if (tmp[0] != '\0')
	{
		lst_size = ft_lstsize(*lst);
		if (ft_lstadd_back(lst, ft_lstnew(ft_strdup(tmp))) == -1)
			return (MALLOC_ERR);
		*i += ft_strlen(tmp);
	}
	else
		*i += 2;
	free(tmp);
	return (0);
}

static size_t	count_space(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

static char *remove_spaces(char *str)
{
	char	*buff;
	char	*new_str;
	int		i;
	char	last;

	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!buff)
		return (NULL);
	i = 0;
	last = 0;
	while (*str)
	{
		if (*str == ' ' && last == ' ')
		{
			last = *str;
			str++;
			continue ;
		}
		buff[i] = *str;
		last = *str;
		i++;
		str++;
	}
	buff[i] = '\0';
	new_str = ft_strdup(buff);
	free(buff);
	return (new_str);
}

static int	add_str(t_list **lst, const char *line, size_t *i)
{
	char	*tmp;
	char	*new_str;
	size_t	j;
	size_t	lst_size;

	tmp = ft_calloc(get_str_len(&line[*i]) + 1, sizeof(char));
	if (!tmp)
		return (MALLOC_ERR);
	j = 0;
	while (line[*i] && !(line[*i] == '\'' || line[*i] == '\"'))
	{
		tmp[j] = line[*i];
		(*i)++;
		j++;
	}
	tmp[j] = '\0';
	new_str = remove_spaces(tmp);
	free(tmp);
	if (!new_str)
		return (MALLOC_ERR);
	lst_size = ft_lstsize(*lst);
	if (ft_lstadd_back(lst, ft_lstnew(ft_strdup(new_str))) == -1)
		return (free(new_str), MALLOC_ERR);
	free(new_str);
	return (0);
}

t_list	*process_quotes(const char *line)
{
	size_t	i;
	t_list	*lst;
	size_t		line_len;

	i = 0;
	lst = NULL;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (add_quotes(&lst, &line[i], &i) == MALLOC_ERR)
			{
				ft_lstclear(&lst, free);
				return (NULL);
			}
		}
		else
		{
			if (add_str(&lst, line, &i) == MALLOC_ERR)
			{
				ft_lstclear(&lst, free);
				return (NULL);
			}
		}
	}
	return (lst);
}
