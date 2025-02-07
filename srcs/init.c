#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>

static char	*process_dollar_sign(const char *str, char *expanded_str, int *i, int last_cmd)
{
	size_t	j;
	char	*var_name;
	char	*var_value;

	if (str[*i + 1] == '$')
	{
		expanded_str = ft_strjoin(expanded_str, "$$");
		*i += 2;
	}
	else if (str[*i + 1] == '?')
	{
		expanded_str = ft_strjoin(expanded_str, ft_itoa(last_cmd));
		*i += 2;
	}
	else if (str[*i + 1] && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'))
	{
		(*i)++;
		j = 0;
		while (str[*i + j] && (ft_isalnum(str[*i + j]) || str[*i + j] == '_'))
			j++;
		var_name = ft_substr(str, *i, j);
		if (!var_name)
			return (NULL);
		var_value = getenv(var_name);
		free(var_name);
		if (var_value)
			expanded_str = ft_strjoin(expanded_str, var_value);
		*i += j;
	}
	else
	{
		expanded_str = ft_charjoin(expanded_str, '$');
		(*i)++;
	}
	return (expanded_str);
}

char	*expand_env_var(char *str, char **env, int last_cmd)
{
	char	*expanded_str;
	int		i;
	int		in_quote;
	char	quote;

	expanded_str = "";
	i = 0;
	in_quote = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		if (i && str[i] == '$' && str[i - 1] != '\'' && str[i - 1] != '\"' && str[i - 1] != '\\')
			break ;
		else if (str[i] == '$' && str[i - 1] != '\\' && quote != '\'')
			expanded_str = process_dollar_sign(str, expanded_str, &i, last_cmd);
		else if (str[i] != '\\')
			expanded_str = ft_charjoin(expanded_str, str[i]);
		if (!expanded_str)
			return (NULL);
		i++;
	}
	free(str);
	if (quote)
		expanded_str = ft_strcpy_expect_char(expanded_str, quote);
	return (expanded_str);
}

static void	handle_redirection_right(t_command *cmd, char *cmd_str, int *i)
{
	int		flag;
	int		j;
	int		k;
	char	*file;

	while (cmd_str[*i] && cmd_str[*i] != '>')
		(*i)++;
	if (cmd_str[*i] && cmd_str[*i + 1] == '>')
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	while (cmd_str[*i] && (cmd_str[*i] == '>' || cmd_str[*i] == ' '))
		(*i)++;
	if (!cmd_str[*i])
		return ;
	cmd->n_args -= 2;
	j = *i;
	while (cmd_str[j] && cmd_str[j] != ' ')
		j++;
	j++;
	file = malloc(j - *i);
	if (!file)
		return ;
	k = 0;
	while (*i + k < j - 1)
	{
		file[k] = cmd_str[*i + k];
		k++;
	}
	file[k] = 0;
	if (cmd->fd_out != 0 && cmd->fd_out != 1)
		close(cmd->fd_out);
	cmd->fd_out = open(file, O_WRONLY | O_CREAT | flag, 0644);
	free(file);
	*i += k + 1;
}

static void	handle_redirection_left(t_command *cmd, char *cmd_str, int *i)
{
	int		j;
	int		k;
	char	*file;
	int		db_redir;

	while (cmd_str[*i] && cmd_str[*i] != '<')
		(*i)++;
	if (cmd_str[*i] && cmd_str[*i + 1] == '<')
		db_redir = 1;
	else
		db_redir = 0;
	while (cmd_str[*i] && (cmd_str[*i] == '<' || cmd_str[*i] == ' '))
		(*i)++;
	if (!cmd_str[*i])
		return ;
	cmd->n_args -= 2;
	j = *i;
	while (cmd_str[j] && cmd_str[j] != ' ')
		j++;
	j++;
	file = malloc(j - *i);
	if (!file)
		return ;
	k = 0;
	while (*i + k < j - 1)
	{
		file[k] = cmd_str[*i + k];
		k++;
	}
	file[k] = 0;
	if (cmd->fd_in != 0 && cmd->fd_in != 1)
		close(cmd->fd_in);
	if (db_redir)
	{
		heredoc(cmd, file);
		cmd->fd_in = open("/tmp/", __O_TMPFILE | O_RDWR, 0644);
	}
	else
		cmd->fd_in = open(file, O_RDONLY, 0644);
	free(file);
	*i += k + 1;
}

static void	handle_redirection(t_command *cmd, char *cmd_str, int is_last)
{
	int		i;
	int		temp;

	i = 0;
	while (cmd_str[i])
	{
		temp = i;
		if (ft_strchr(&cmd_str[i], '<'))
			handle_redirection_left(cmd, cmd_str, &i);
		else if (ft_strchr(&cmd_str[i], '>'))
			handle_redirection_right(cmd, cmd_str, &i);
		if (!(ft_strchr(&cmd_str[temp], '>')) && !ft_strchr(&cmd_str[i], '<')
			&& !ft_strchr(&cmd_str[i], '>') && is_last)
		{
			cmd->fd_out = 1;
			break ;
		}
		else if (!ft_strchr(&cmd_str[i], '<')
			&& !ft_strchr(&cmd_str[i], '>'))
			break ;
		while (cmd_str[i] == ' ')
			i++;
	}
}

static int	init_cmd(t_command *cmd, char *cmd_str, char **env, int is_last, int last_cmd)
{
	char		**args;
	char		**paths;
	static int	pipefd[2] = {-1};
	int			i;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (pipefd[0] != -1)
		cmd->fd_in = pipefd[0];
	args = ft_split(cmd_str, ' ');
	if (!args)
		return (0);
	paths = get_paths(env);
	if (!paths)
		return (0);
	cmd->args = args;
	cmd->n_args = 0;
	while (args[cmd->n_args])
		cmd->n_args++;
	cmd->path = get_cmd_path(paths, *cmd);
	if (!cmd->path)
		return (0);
	if (pipe(pipefd) != -1)
		cmd->fd_out = pipefd[1];
	handle_redirection(cmd, cmd_str, is_last);
	i = -1;
	while (++i < cmd->n_args)
	{
		cmd->args[i] = expand_env_var(cmd->args[i], env, last_cmd);
		if (!cmd->args[i])
			return (0);
	}
	return (1);
}

int	init_table(char *line, char **env, t_command_table *table, int last_cmd)
{
	char				**cmd_strs;
	size_t				i;

	cmd_strs = ft_split(ft_strtrim(line, " \t"), '|');
	if (!cmd_strs)
		return (127);
	table->n_commands = 0;
	while (cmd_strs[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return (127);
	i = 0;
	while (i < table->n_commands)
	{
		if (!init_cmd(&table->commands[i], cmd_strs[i], env, i == table->n_commands - 1, last_cmd))
			return (127);
		i++;
	}
	return (1);
}
