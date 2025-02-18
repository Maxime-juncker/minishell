#include "minishell.h"

static char	*append_str(char *old, char *append_str, int new_len)
{
	char	*new_str;

	if (!old)
		return (ft_strdup(append_str));
	new_str = malloc(new_len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old, new_len);
	free(old);
	ft_strlcat(new_str, append_str, new_len);
	return (new_str);
}

static int	heredoc(t_command *cmd, char *deli)
{
	char	*doc;
	char	*line;
	size_t	len;

	cmd->fd_in = open("/tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	doc = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			printf("minishell: warning: %s (wanted `%s')\n",
				"here-document delimited by end-of-file", deli);
		len = ft_strlen(line) - 1;
		if (!line || !ft_strncmp(line, deli, len) && ft_strlen(deli) == len)
		{
			if (line)
				free(line);
			break ;
		}
		doc = append_str(doc, line, ft_strlen(doc) + len + 2);
		free(line);
		if (!doc)
			return (1);
	}
	if (doc)
		write(cmd->fd_in, doc, ft_strlen(doc));
	close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644);
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

static char	*get_file_name(char **s)
{
	int		i;
	char	quote;
	char	*file;
	int		start;
	char	*temp;

	i = 0;
	quote = 0;
	start = 0;
	while ((*s)[start] == ' ' || (*s)[start] == '>' || (*s)[start] == '<')
		start++;
	i = start;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' || (*s)[i] == '\"')
			quote = toggle_quote(quote, (*s)[i]);
		if ((*s)[i] == ' ' && !quote)
			break ;
		i++;
	}
	temp = ft_substr((*s), start, i - start);
	if (temp == NULL)
		return (NULL);
	file = remove_quotes_pair(temp);
	free(temp);
	*s += i;
	return (file);
}

static void	handle_redir(t_command *cmd, char **command, char c, int db_redir)
{
	char	*file;
	char	*start;
	char	**args;
	int		i;
	char	*temp;

	file = get_file_name(command);
	if (!file)
		return ;
	while (command && **command == ' ')
		(*command)++;
	start = *command;
	while (**command && **command != '>' && **command != '<')
		(*command)++;
	temp = ft_substr(start, 0, *command - start);
	args = ft_split(temp, ' ');
	free(temp);
	if (!args)
		return ;
	if (args[0])
	{
		i = 0;
		while (args[i])
		{
			cmd->args[cmd->n_args] = ft_strdup(args[i]);
			free(args[i]);
			cmd->n_args++;
			i++;
		}
	}
	free(args);
	handle_fd(cmd, file, c, db_redir);
}

void	redir(t_command *cmd, char *command, int is_last, int i)
{
	char	*temp;

	temp = command;
	cmd->n_args = 0;
	while (cmd->args[cmd->n_args] && cmd->args[cmd->n_args][0] != '>'
		&& cmd->args[cmd->n_args][0] != '<')
		cmd->n_args++;
	while (*command)
	{
		if (*command == '<' && *command == '>')
		{
			handle_redir(cmd, &command, '>', *(command + 1) == '<');
			cmd->fd_out = 1;
		}
		else if (*command == '<')
			handle_redir(cmd, &command, '<', *(command + 1) == '<');
		else if (*command == '>')
			handle_redir(cmd, &command, '>', *(command + 1) == '>');
		else
			command++;
		if (cmd->fd_in == -1)
			break ;
	}
	if (is_last && !ft_strchr(temp, '>'))
		cmd->fd_out = 1;
	if (!i && !ft_strchr(temp, '<'))
		cmd->fd_in = 0;
}
