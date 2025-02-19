#include "minishell.h"

static int	error_symbol(char error_symb, const char *cmd_line, int i)
{
	int	occ;
	int	max_occ;

	if (error_symb == '<' && cmd_line[i + 1] == '>')
	{
		printf("minishell: syntax error near unexpected token `<>\'\n");
		return (SYNTAX_ERR);
	}
	max_occ = 2;
	occ = 0;
	printf("minishell: syntax error near unexpected token `");
	while (cmd_line[i] == error_symb && occ < max_occ)
	{
		printf("%c", error_symb);
		i++;
		occ++;
	}
	printf("\'\n");
	return (SYNTAX_ERR);
}

int	check_redir_out(const char *cmd_line, int i)
{
	int		occ;
	int		max_occ;
	char	error_symb;

	i++;
	if (cmd_line[i] == '>')
		return (0);
	while (cmd_line[i])
	{
		if (cmd_line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (cmd_line[i] != '|' && cmd_line[i] != '<' && cmd_line[i] != '>')
			return (0);
		error_symb = cmd_line[i];
		return (error_symbol(error_symb, cmd_line, i));
	}
	return (0);
}

static char	*get_file_name(const char *s)
{
	int		i;
	char	quote;
	char	*file;
	int		start;

	i = 0;
	quote = 0;
	start = 0;
	while (s[start] == ' ' || s[start] == '>' || s[start] == '<')
		start++;
	i = start;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			quote = toggle_quote(quote, s[i]);
		if (s[i] == ' ' && !quote)
			break ;
		i++;
	}
	file = ft_strdup(ft_substr(s, start, i - start));
	if (file == NULL)
		return (NULL);
	file = remove_quotes_pair(file);
	return (file);
}

int	skip_check_in(const char *cmd_line, int i)
{
	if (i > 0)
	{
		if (cmd_line[i + 1] == '<' || cmd_line[i - 1] == '<'
			|| cmd_line[i + 1] == '>' || cmd_line[i + 1] == '\0')
			return (1);
	}
	else if (cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>'
		|| cmd_line[i + 1] == '\0')
		return (1);
	while (cmd_line[i] == ' ')
		i++;
	if (cmd_line[i] == '\0')
		return (1);
	return (0);
}

int	check_redir_in(const char *cmd_line, int i)
{
	char	*file;

	if (skip_check_in(cmd_line, i))
		return (0);
	file = get_file_name(cmd_line + i);
	if (file == NULL)
	{
		return (new_line_error(cmd_line + i, '<'));
	}
	if (access(file, F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (1);
	}
	return (0);
}
