#include "minishell.h"
#include <dirent.h>

char	**realloc_patern(char **patern)
{
	char	**new_patern;
	int		i;

	if (patern == NULL)
		return (NULL);
	i = 0;
	while (patern[i])
		i++;
	new_patern = ft_calloc(i + 1, sizeof(char*));
	if (malloc_assert(new_patern, INFO))
		return (cleanup_arr((void** )patern), NULL);
	i = 0;
	while (patern[i])
	{
		new_patern[i] = patern[i];
		i++;
	}
	new_patern[i] = NULL;
	free(patern);
	return (new_patern);
}

char	**new_patern(char *line)
{
	char	**patern;
	int		i;
	int		j;

	patern = ft_calloc(ft_strlen(line) + 1, sizeof(char *));
	if (malloc_assert(patern, INFO))
		return(NULL);
	i = 0;
	j = 0;
	while (*line && *line != ' ')
	{
		if (*line != '*')
		{
			i = 0;
			while (line[i] && line[i] != ' ' && line[i] != '*')
				i++;

			patern[j] = ft_substr(line, 0, i);
			if (malloc_assert(patern[j], INFO))
				return (NULL);
			j++;
			line += i;
		}
		else
		{
			if (j == 0 || patern[j - 1][0] != '*')
			{
				patern[j] = ft_strdup("*");
				if (malloc_assert(patern[j], INFO))
					return (NULL);
				while (*line == '*')
					line++;
				j++;
			}
		}
	}
	patern[j] = NULL;
	return (realloc_patern(patern));
}

int	add_file(char *file_name, char **patern)
{
	int		i;
	char	*tmp;
	char	*new_tmp;

	tmp = file_name;
	i = 0;
	while (patern[i])
	{
		if (patern[i + 1] == NULL)
			break;
		if (patern[i][0] == '*')
		{
			if (patern[i + 2] == NULL)
			{
				i++;
				break;
			}
			tmp = ft_strnstr(tmp, patern[i + 1], ft_strlen(tmp));
			if (tmp == NULL)
				return (0);
			i++;
			continue ;
		}
		new_tmp = ft_strnstr(tmp, patern[i], ft_strlen(tmp));
		if (new_tmp == NULL)
			return (0);
		while (tmp == new_tmp)
		{
			tmp += ft_strlen(patern[i]);
			new_tmp = ft_strnstr(tmp, patern[i], ft_strlen(tmp));
		}
		i++;
	}
	if (patern[i][0] == '*')
		return (1);
	tmp = ft_strrstr(tmp, patern[i]);
	if (tmp == NULL)
		return (0);
	if (ft_strlen(tmp) == ft_strlen(patern[i]))
		return (1);
	return (0);
}

char	*expand_wildcard(char *line)
{
	DIR				*dir;
	struct dirent*	infos;
	char			*expanded;
	char			**patern;

	if (ft_strchr(line, '*') == NULL)
		return (ft_strdup(line));
	dir = opendir(".");
	if (!dir)
		return (perror("can't open dir"), NULL);
	patern = new_patern(line);
	if (patern == NULL)
		return (closedir(dir), NULL);
	expanded = NULL;
	infos = readdir(dir);
	while (infos)
	{
		if (infos->d_name[0] != '.')
		{
			if (add_file(infos->d_name, patern))
			{
				expanded = ft_strjoin_free(expanded, infos->d_name, FREE1);
				if (malloc_assert(expanded, INFO))
					return (closedir(dir), cleanup_arr((void **)patern), NULL);
				expanded = ft_charjoin(expanded, ' ');
				if (!expanded)
					return (closedir(dir), cleanup_arr((void **)patern), NULL);
			}
		}
		infos = readdir(dir);
	}
	closedir(dir);
	cleanup_arr((void **)patern);
	if (expanded == NULL)
		return (ft_strdup(line));
	return (expanded);

}

char	*add_wildcard(char *line)
{
	if (line[0] == '\'' || line[0] == '\"')
		return (ft_strdup(line));
	return (expand_wildcard(line));
}

char	*process_wildcard(char *line)
{
	t_list	*lst;
	t_list	*first;
	char	*result;

	if (!line)
		return (NULL);
	lst = split_line(line);
	free(line);
	if (!lst)
		return (NULL);
	first = lst;
	result = NULL;
	while (lst)
	{
		result = ft_strjoin_free(result, add_wildcard((char *)lst->content), FREE1 | FREE2);
		if (!result)
			return (malloc_assert(NULL, INFO), ft_lstclear(&first, free), NULL);
		if (lst->next)
			result = ft_charjoin(result, ' ');
		lst = lst->next;
	}
	ft_lstclear(&first, free);
	return (result);
}
