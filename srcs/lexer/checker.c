#include "minishell.h"

t_list	*split_line(char *line)
{
	t_list	*lst;
	char	*tmp;
	int		i;
	char	quote;

	lst = NULL;
	tmp = NULL;
	i = 0;
	quote = 0;
	while (line[i])
	{
		quote = toggle_quote(line[i], quote);
		if (quote == 0 && line[i] == ' ')
		{
			if (tmp)
			{
				if (ft_lstadd_back(&lst, ft_lstnew(ft_strdup(tmp))) == -1)
				{
					ft_lstclear(&lst, free);
					free(tmp);
					return (NULL);
				}
				free(tmp);
			}
			tmp = NULL;
			i++;
			continue ;
		}
		tmp = ft_charjoin(tmp, line[i]);
		if (tmp == NULL)
			return (NULL);
		i++;
	}
	if (tmp)
	{
		if (ft_lstadd_back(&lst, ft_lstnew(ft_strdup(tmp))) == -1)
		{
			ft_lstclear(&lst, free);
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	return (lst);
}

// syntax check in the following order: pipe, redirection, cmd / dir
int	check_cmd_line( const char *process_line, char **env )
{
	int		code;
	char	**cmd_parts;
	int		i;
	int		tmp;

	if (!process_line)
		return (0);
	code = check_syntax(process_line);
	if (code != 0)
		return (code);
	cmd_parts = ft_split(process_line, '|');
	if (cmd_parts == NULL)
		return (MALLOC_ERR);
	i = 0;
	code = 0;
	while (cmd_parts[i])
	{
		tmp = check_path(cmd_parts[i], env);
		if (tmp != 0)
			code = tmp;
		i++;
	}
	cleanup_arr((void **)cmd_parts);
	return (code);
}
