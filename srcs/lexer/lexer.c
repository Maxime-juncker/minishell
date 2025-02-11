#include "minishell.h"

#if SHOW_LEXER

char	*process_line(const char *cmd_line)
{
	t_list	*process_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	process_lst = process_quotes(cmd_line);
	process_str = process_expanded_vars(process_lst, env);

	ft_printf("------------------------------ lexer output ------------------------------\n");
	ft_printf("process_str: %s\n", process_str);
	ft_printf("process_lst: ");
	ft_lstprint(process_lst);
	ft_printf("--------------------------------------------------------------------------\n");
	ft_lstclear(&process_lst, free);
	return (process_str);
}

#else

char	*process_line(const char *cmd_line, char **env)
{
	t_list	*process_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	process_lst = process_quotes(cmd_line);
	if (!process_lst)
		return (NULL);
	process_str = process_expanded_vars(process_lst, env);
	ft_lstclear(&process_lst, free);
	return (process_str);
}

#endif

