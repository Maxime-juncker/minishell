#include "minishell.h"

char	*process_line(const char *cmd_line)
{
	t_list	*process_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	process_lst = process_quotes(cmd_line);
	process_str = process_expanded_vars(process_lst);
	ft_lstclear(&process_lst, free);
	printf("%s$\n", process_str);
	return (process_str);
}
