#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static char	*handle_dollar(const char *str, int *i, int last_cmd)
{
	size_t	j;
	char	*var_name;
	char	*var_value;

	if (str[*i + 1] == '$')
		return (*i += 1, ft_strdup("$$"));
	else if (str[*i + 1] == '?')
		return (*i = ft_strlen(str), ft_itoa(last_cmd));
	else if (ft_isdigit(str[*i + 1]) && str[*i + 1] == '0')
		return (*i += 2, ft_strdup("minishell"));
	else if (ft_isdigit(str[*i + 1]))
		return (*i += 2, ft_strdup(""));
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
		*i = ft_strlen(str);
		if (var_value)
			return (ft_strdup(var_value));
		return (ft_strdup(""));
	}
	return (*i += 1, ft_strdup("$"));
}

char	*expand_env_var(char *str, char **env, int last_cmd)
{
	char	*expanded_str;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	expanded_str = handle_dollar(str, &i, last_cmd);
	while (ft_isalnum(str[i]) || str[i] == ' ')
	{
		expanded_str = ft_charjoin(expanded_str, str[i]);
		i++;
	}
	free(str);
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
	args = ft_split_1space(cmd_str, ' ');
	if (!args)
		return (0);
	paths = get_paths(env);
	if (!paths)
		return (cleanup_arr((void **)args), 0);
	cmd->args = args;
	cmd->n_args = 0;
	while (args[cmd->n_args])
		cmd->n_args++;
	cmd->path = get_cmd_path(paths, *cmd);
	if (!cmd->path)
	{
		cleanup_arr((void **)args);
		return (0);
	}
	if (pipe(pipefd) != -1)
		cmd->fd_out = pipefd[1];
	else
	{
		cleanup_arr((void **)args);
		free(cmd->path);
		return (0);
	}
	redir(cmd, cmd_str, is_last);
	return (1);
}

int	init_table(char *line, char **env, t_command_table *table, int last_cmd)
{
	char	**cmd_strs;
	size_t	i;

	while (*line == ' ' || *line == '\t')
		line++;
	cmd_strs = ft_split(line, '|');
	if (!cmd_strs)
		return (127);
	table->n_commands = 0;
	while (cmd_strs[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return (free_all(cmd_strs), 127);
	i = 0;
	while (i < table->n_commands)
	{
		if (!init_cmd(&table->commands[i], cmd_strs[i],
				env, i == table->n_commands - 1))
			return (free_all(cmd_strs), free(table->commands), 127);
		i++;
	}
	return (free_all(cmd_strs), 1);
}
