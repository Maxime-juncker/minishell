#include "minishell.h"

static char	*append_str(char *old, char *append_str, int new_len)
{
	char	*new_str;

	new_str = malloc(new_len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old, new_len);
	ft_strlcat(new_str, append_str, new_len);
	free(old);
	return (new_str);
}

static int	heredoc(t_command *cmd, char *deli)
{
	char	*doc;
	char	*line;
	size_t	len;

	doc = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			printf("minishell: warning: %s\n",
				"here-document delimited by end-of-file (wanted `EOF')");
		len = ft_strlen(line) - 1;
		if (!line || (!ft_strncmp(line, deli, len) && ft_strlen(deli) == len))
			break ;
		if (!doc)
			doc = ft_strdup(line);
		else
			doc = append_str(doc, line, ft_strlen(doc) + len + 2);
		free(line);
		if (!doc)
			return (1);
	}
	printf("%s", doc);
	cmd->fd_in = open("/tmp/", __O_TMPFILE | O_RDWR, 0644);
	return (free(doc), 0);
}

static void	handle_fd(t_command *cmd, char *file, char c, int db_redir)
{
	if (c == '>')
	{
		if (cmd->fd_out != 0 && cmd->fd_out != 1)
			close(cmd->fd_out);
		if (db_redir)
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (cmd->fd_in != 0 && cmd->fd_in != 1)
			close(cmd->fd_in);
		if (db_redir)
			heredoc(cmd, file);
		else
			cmd->fd_in = open(file, O_RDONLY, 0644);
	}
	free(file);
}

static void	handle_redir(t_command *cmd, char *cmd_str, int *i, char c)
{
	int		j;
	int		k;
	char	*file;
	int		db_redir;

	cmd->n_args -= 2;
	while (cmd_str[*i] && cmd_str[*i] != c)
		(*i)++;
	db_redir = (cmd_str[*i] && cmd_str[*i + 1] == c);
	while (cmd_str[*i] && (cmd_str[*i] == c || cmd_str[*i] == ' '))
		(*i)++;
	if (!cmd_str[*i])
		return ;
	j = *i;
	while (cmd_str[j] && cmd_str[j] != ' ')
		j++;
	file = malloc(j - *i + 1);
	if (!file)
		return ;
	k = -1;
	while (*i + ++k < j)
		file[k] = cmd_str[*i + k];
	file[k] = 0;
	*i += k + 1;
	handle_fd(cmd, file, c, db_redir);
}

void	redir(t_command *cmd, char *cmd_str, int is_last)
{
	int		i;
	int		temp;

	i = 0;
	while (cmd_str[i])
	{
		temp = i;
		if (ft_strchr(&cmd_str[i], '>'))
			handle_redir(cmd, cmd_str, &i, '>');
		else if (ft_strchr(&cmd_str[i], '<'))
			handle_redir(cmd, cmd_str, &i, '<');
		if (!(ft_strchr(&cmd_str[temp], '>')) && !ft_strchr(&cmd_str[i], '<')
			&& !ft_strchr(&cmd_str[i], '>') && is_last)
			cmd->fd_out = 1;
		if (!ft_strchr(&cmd_str[i], '>') && !ft_strchr(&cmd_str[i], '<'))
			break ;
		while (cmd_str[i] == ' ')
			i++;
	}
}
