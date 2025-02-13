#include "minishell.h"

char	*join_lst(t_list *lst)
{
	char	*str;
	int		i;
	char	*content;
	int		len;

	str = NULL;
	len = 0;
	while (lst)
	{
		i = 0;
		content = (char *)lst->content;
		while (content[i])
		{
			if (content[i] == ' ' && str && str[len] == ' ')
			{
				i++;
				continue;
			}
			str = ft_charjoin(str, content[i]);
			len++;
			i++;
		}
		lst = lst->next;
	}
	return (str);
}


#if SHOW_LEXER

char	*process_line(const char *cmd_line, char **env, int *code)
{
	t_list	*quotes_lst;
	t_list	*var_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	ft_printf("------------------------------ lexer output ------------------------------\n");
	quotes_lst = process_quotes(cmd_line);
	ft_lstprint("quotes lst: ", quotes_lst);
	var_lst = process_expanded_vars(quotes_lst, env);
	ft_lstprint("var lst: ", var_lst);
	process_str = join_lst(var_lst);
	ft_printf("process str: %s\n", process_str);
	ft_printf("--------------------------------------------------------------------------\n");
	ft_lstclear(&quotes_lst, free);
	ft_lstclear(&var_lst, free);

	*code = check_cmd_line(process_str);
	return (process_str);
}

#else

char	*process_line(const char *cmd_line, char **env, int *code)
{
	t_list	*quotes_lst;
	t_list	*var_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	quotes_lst = process_quotes(cmd_line);
	var_lst = process_expanded_vars(quotes_lst, env);
	process_str = join_lst(var_lst);
	ft_lstclear(&quotes_lst, free);
	ft_lstclear(&var_lst, free);

	*code = check_cmd_line(process_str);
	return (process_str);
}

#endif
