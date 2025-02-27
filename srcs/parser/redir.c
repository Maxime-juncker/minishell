/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/26 17:27:34 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!temp)
		return (malloc_assert(ERR), NULL);
	file = remove_quotes_pair(temp);
	free(temp);
	*s += i;
	if (!file)
		return (malloc_assert(ERR), NULL);
	return (file);
}

static int	handle_redir(t_command *cmd, char **command, char c, int db_redir)
{
	char	*file;
	char	*start;
	char	**args;
	int		i;
	char	*temp;

	file = get_file_name(command);
	if (!file)
		return (MALLOC_ERR);
	start = *command;
	while (**command && **command != '>' && **command != '<')
		(*command)++;
	temp = ft_substr(start, 0, *command - start);
	if (!temp)
		return (free(file), malloc_assert(ERR), MALLOC_ERR);
	args = ft_split(temp, ' ');
	free(temp);
	if (!args)
		return (MALLOC_ERR);
	i = 0;
	while (args[i])
		cmd->args[cmd->n_args++] = args[i++];
	free(args);
	handle_fd(cmd, file, c, db_redir);
	return (0);
}

int	redir(t_command *cmd, char *command)
{
	char	quote;

	cmd->n_args = 0;
	while (cmd->args[cmd->n_args] && cmd->args[cmd->n_args][0] != '>'
		&& cmd->args[cmd->n_args][0] != '<')
		cmd->n_args++;
	quote = 0;
	while (*command)
	{
		quote = toggle_quote(*command, quote);
		if (quote != 0)
		{
			command++;
			continue ;
		}
		if ((*command == '<' || *command == '>') && MALLOC_ERR ==
			handle_redir(cmd, &command, *command, *command == *(command + 1)))
			return (MALLOC_ERR);
		else
			command++;
	}
	return (0);
}
