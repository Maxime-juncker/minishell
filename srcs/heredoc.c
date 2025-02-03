#include "minishell.h"

char *append_str(char *old, char *append_str, int new_lenght)
{
	char	*new_str;
	// char	*old_dup;

	// old_dup = ft_strdup(old;)
	new_str = malloc(new_lenght);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, old, new_lenght);
	ft_strlcat(new_str, append_str, new_lenght);
	return (new_str);
}

int	heredoc(const t_command cmd)
{
	char	*doc;
	char	*line;
	char	*delemiter = "EOF\n"; //! to change with cmd args
	size_t	len;

	doc = NULL;
	line = get_next_line(0);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (ft_strncmp(line, delemiter, len) == 0)
		{
			break;
		}
		if (doc == NULL)
		{
			doc = ft_strdup(line);
			if (doc == NULL)
				return 1;
		}
		else
		{
			doc = append_str(doc, line, ft_strlen(doc) + len + 1);
			if (doc == NULL)
				return (1);
		}
		free(line);
		line = get_next_line(0);
	}
	ft_printf("%s", doc);
}
