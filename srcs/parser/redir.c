/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/28 17:47:01 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls -l > 1 -a

#include "minishell.h"

static void	handle_fd(t_command *cmd, char *file, char c, int db_redir)
{
	if (c == '>')
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		if (db_redir)
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		if (db_redir)
			heredoc(cmd, file);
		else
			cmd->fd_in = open(file, O_RDONLY, 0644);
	}
	free(file);
}

static char	*get_file(char **s, int start, int i)
{
	char	*temp;
	char	*res;

	temp = ft_substr((*s), start, i - start);
	if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	res = remove_quotes_pair(temp);
	free(temp);
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	return (res);
}

static char	*get_file_name(char **s)
{
	int		i;
	char	quote;
	char	*file;
	int		start;

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
	file = get_file(s, start, i);
	*s += i;
	if (!file)
		return (NULL);
	return (file);
}

static int	handle_redir(t_command *cmd, char **command, char c, int db_redir)
{
	char	*file;
	char	*temp;
	int		i;
	int		j;

	file = get_file_name(command);
	if (!file)
		return (MALLOC_ERR);
	if (cmd->args[0][0] == '>' || cmd->args[0][0] == '<')
	{
		temp = cmd->args[0];
		cmd->args[0] = cmd->args[2];
		cmd->args[2] = temp;
		cmd->n_args = 1;
	}
	i = 3;
	j = 1;
	while (cmd->args[i] && ft_strcmp(cmd->args[i], file)
		&& cmd->args[i][0] != '>' && cmd->args[i][0] != '<')
	{
		free(cmd->args[j]);
		cmd->args[j++] = ft_strdup(cmd->args[i++]);
		cmd->n_args++;
	}
	return (handle_fd(cmd, file, c, db_redir), 0);
}

int	redir(t_command *cmd, char *command)
{
	char	quote;

	quote = 0;
	while (*command)
	{
		if (*command == '\'' || *command == '\"')
			quote = toggle_quote(*command, quote);
		if (quote != 0)
		{
			command++;
			continue ;
		}
		if (*command == '<' || *command == '>')
		{
			if (handle_redir(cmd, &command, *command,
					*command == *(command + 1)) == MALLOC_ERR)
				return (MALLOC_ERR);
		}
		else
			command++;
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
			return (1);
	}
	return (0);
}
