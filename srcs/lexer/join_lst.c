#include "minishell.h"

static int skip_spaces( char content_c, char *str_ref, char quote, int len )
{
	if (content_c == ' ' && !str_ref)
	{
		return (1);
	}
	if (!quote && content_c == ' ' && str_ref \
		&& len > 0 && str_ref[len - 1] == ' ')
	{
		return (1);
	}
	return (0);
}

static void join_loop(char *content, char **str_ref)
{
	int len;
	int i;
	char quote;

	i = 0;
	quote = 0;
	len = 0;
	while (content[i])
	{
		while (skip_spaces(content[i], *str_ref, quote, len))
			i++;
		quote = toggle_quote(content[i], quote);
		if ((*str_ref && !is_symbol((*str_ref)[len - 1]) && (*str_ref)[len - 1] != ' ' && is_symbol(content[i])) ||
			(*str_ref && is_symbol((*str_ref)[len - 1]) && content[i] != ' ' && !is_symbol(content[i])))
		{
			*str_ref = ft_charjoin(*str_ref, ' ');
			len++;
			continue ;
		}
		*str_ref = ft_charjoin(*str_ref, content[i]);
		len++;
		i++;
	}
}

char	*join_lst(t_list *lst)
{
	char	*str;
	char	*content;

	str = NULL;
	while (lst)
	{
		join_loop(lst->content, &str);
		lst = lst->next;
	}
	return (str);
}