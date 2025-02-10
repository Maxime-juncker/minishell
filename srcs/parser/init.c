#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*process_dollar_sign(const char *str, char *expanded_str, int *i, int last_cmd)
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
	char	quote;

	expanded_str = NULL;
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		if (i && str[i] == '$' && str[i - 1] != '\'')
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

static int	init_cmd(t_command *cmd, char *cmd_str, char **env, int is_last)
{
	char		**args;
	char		**paths;
	static int	pipefd[2] = {-1};

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
	redir(cmd, cmd_str, is_last);
	return (1);
}

int	init_table(char *line, char **env, t_command_table *table, int last_cmd)
{
	char	**cmd_strs;
	size_t	i;

	cmd_strs = ft_split(line, '|');
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
		if (!init_cmd(&table->commands[i], cmd_strs[i],
				env, i == table->n_commands - 1))
			return (127);
		i++;
	}
	return (1);
}
