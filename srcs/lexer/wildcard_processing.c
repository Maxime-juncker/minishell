#include "minishell.h"
#include <dirent.h>
// echo *

//TODO: si wildcard exist pas (ex *.egherugh) alors faut laisser la wildcard dans line

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	printf("%s", GRAY);
	while (arr[i])
	{
		printf("%s, ", arr[i]);
		i++;
	}
	printf("%s", RESET);
	printf("\n");
}

char	**new_patern(char *line)
{
	char	**patern;
	int		i;
	int		j;

	patern = malloc(500);
	if (!patern)
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
			
			patern[j] = ft_strdup(ft_substr(line, 0, i));
			j++;
			line += i;
		}
		else
		{
			if (j == 0 || patern[j - 1][0] != '*')
			{
				patern[j] = ft_strdup("*");
				j++;
			}
			line++;
		}
	}
	patern[j] = NULL;
	// print_arr(patern);
	return (patern);
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
		if (patern[i][0] == '*')
		{
			if (patern[i + 1] == NULL)
				return (1);
			while (*tmp && patern[i + 1][0] != *tmp)
				tmp++;
			if (!*tmp)
				return (0);
			i++;
		}
		new_tmp = ft_strnstr(tmp, patern[i], ft_strlen(tmp));
		if (tmp == new_tmp)
			tmp += ft_strlen(patern[i]);
		else
			i++;
	}
	if (patern[i - 1][0] == '*')
		return (1);
	if (tmp[0] == '\0')
		return (1);
	return (0);
}

int		expand_needed(char **patern)
{
	int	i;

	i = 0;
	while (patern[i])
	{
		if (ft_strchr(patern[i], '*') != NULL)
			return (1);
		i++;
	}
	return (0);
}

char	*expand_wildcard(char *line)
{
	DIR				*dir;
	struct dirent*	infos;
	char			*expanded;
	char			**patern;
	
	expanded = NULL;
	dir = opendir(".");
	patern = new_patern(line);
	if (patern == NULL)
		return (NULL);
	if (expand_needed(patern) == 0)
		return (ft_strdup(line));
	if (dir)
	{
		infos = readdir(dir);
		while (infos)
		{
			if (infos->d_name[0] != '.')
			{
				if (add_file(infos->d_name, patern))
				{
					expanded = ft_strjoin_free(expanded, infos->d_name, FREE1);
					expanded = ft_charjoin(expanded, ' ');
					if (!expanded)
						return (closedir(dir), NULL);
				}
			}
			// printf("%s\n", infos->d_name);
			infos = readdir(dir);
		}
		closedir(dir);
	}
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
	char	*result;

	if (!line)
		return (NULL);
	lst = split_line(line);
	if (!lst)
		return (free(line), NULL);
	result = NULL;
	while (lst)
	{
		result = ft_strjoin_free(result, add_wildcard((char *)lst->content), FREE1 | FREE2);
		if (lst->next)
			result = ft_charjoin(result, ' ');
		lst = lst->next;
	}
	free(line);
	return (result);
}
