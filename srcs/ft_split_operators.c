#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int	is_operator(const char *s)
{
	return ((s[0] == '&' && s[1] == '&') || (s[0] == '|' && s[1] == '|'));
}

static int	count_words(const char *s)
{
	int		count;
	int		paren_count;

	count = 0;
	paren_count = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == '(')
		{
			paren_count++;
			count++;
			while (*s && (*s != ')' || paren_count > 1))
			{
				if (*s == '(')
					paren_count++;
				else if (*s == ')')
					paren_count--;
				s++;
			}
			if (*s == ')')
				s++;
		}
		else if (is_operator(s))
		{
			count++;
			s += 2;
		}
		else if (*s)
		{
			count++;
			while (*s && !is_operator(s) && *s != '(')
				s++;
		}
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*res;
	size_t	i;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	free_all(char **res, int i)
{
	while (--i != -1)
		free(res[i]);
	free(res);
}

char	**ft_split_operators(const char *s)
{
	char	**res;
	int		i;
	size_t	len;
	int		paren_count;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	paren_count = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == '(')
		{
			paren_count++;
			len = 1;
			while (s[len] && (s[len] != ')' || paren_count > 1))
			{
				if (s[len] == '(')
					paren_count++;
				else if (s[len] == ')')
					paren_count--;
				len++;
			}
			res[i] = ft_strndup(s, len);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += len;
			if (*s == ')')
				s++;
		}
		else if (is_operator(s))
		{
			res[i] = ft_strndup(s, 2);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += 2;
		}
		else if (*s)
		{
			len = 0;
			while (s[len] && !is_operator(s + len) && s[len] != '(')
				len++;
			res[i] = ft_strndup(s, len);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += len;
		}
	}
	res[i] = NULL;
	return (res);
}
