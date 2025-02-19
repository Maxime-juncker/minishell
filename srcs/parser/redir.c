#include "minishell.h"

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

// static char	*get_file_name(char **s)
// {
// 	char	quote;
// 	char	*file;
// 	char	*start;
// 	char	*temp;

// 	quote = 0;
// 	while (**s == ' ' || **s == '>' || **s == '<')
// 		(*s)++;
// 	start = *s;
// 	while (**s)
// 	{
// 		if (**s == '\'' || **s == '\"')
// 			quote = toggle_quote(quote, **s);
// 		if (**s == ' ' && !quote)
// 			break ;
// 		(*s)++;
// 	}
// 	temp = ft_substr(start, 0, *s - start);
// 	if (!temp)
// 		return (NULL);
// 	file = remove_quotes_pair(temp);
// 	free(temp);
// 	return (file);
// }

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
	start = *command;
	while (**command && **command != '>' && **command != '<')
		(*command)++;
	temp = ft_substr(start, 0, *command - start);
	args = ft_split(temp, ' ');
	free(temp);
	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		cmd->args[cmd->n_args++] = ft_strdup(args[i]);
		free(args[i++]);
	}
	free(args);
	handle_fd(cmd, file, c, db_redir);
}

void	redir(t_command *cmd, char *command)
{
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
}
