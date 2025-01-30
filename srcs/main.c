#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>

static char	*process_dollar_sign(const char *str, char *expanded_str, int *i)
{
	size_t	j;
	char	*var_name;
	char	*var_value;

	if (str[*i + 1] == '$')
	{
		expanded_str = ft_strjoin(expanded_str, "$$");
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
		expanded_str = ft_strjoin(expanded_str, "$");
		(*i)++;
	}
	return (expanded_str);
}

static char	*expand_env_var(const char *str, char **env)
{
	char	*expanded_str;
	int		i;

	expanded_str = "";
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			expanded_str = process_dollar_sign(str, expanded_str, &i);
		else
		{
			expanded_str = ft_charjoin(expanded_str, str[i]);
			i++;
		}
		if (!expanded_str)
			return (NULL);
	}
	return (expanded_str);
}

static int	handle_redirection(t_command *cmd, char *cmd_str)
{
	char	*input_file;
	char	*output_file;

	input_file = ft_strchr(cmd_str, '<');
	if (input_file)
	{
		*input_file = '\0';
		input_file++;
		while (*input_file == ' ' || *input_file == '\t')
			input_file++;
		cmd->fd_in = open(input_file, O_RDONLY);
		if (cmd->fd_in == -1)
		{
			perror("Error opening input file");
			return (0);
		}
		cmd->n_args -= 2;
	}
	output_file = ft_strchr(cmd_str, '>');
	if (output_file)
	{
		*output_file = '\0';
		output_file++;
		while (*output_file == ' ' || *output_file == '\t')
			output_file++;
		cmd->fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
		{
			perror("Error opening output file");
			return (0);
		}
		cmd->n_args -= 2;
	}
	return (1);
}

static int	handle_pipe_redirection(t_command *cmd, int *pipe_fd)
{
	cmd->fd_out = pipe_fd[1];
	if (pipe_fd[0] != -1)
		cmd->fd_in = pipe_fd[0];
	return (1);
}

static int	init_cmd(t_command *cmd, char *cmd_str, char **env)
{
	char		**args;
	char		**paths;
	static int	pipefd[2] = {-1};
	int			i;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (pipefd[0] != -1)
	{
		cmd->fd_in = pipefd[0];
	}
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
	i = -1;
	while (++i < cmd->n_args)
		cmd->args[i] = expand_env_var(cmd->args[i], env);
	// if (!handle_pipe_redirection(cmd, pipe_fd))
	// 	return (0);
	if (pipe(pipefd) != -1);
	{
		cmd->fd_out = pipefd[1];
	}
	if (!handle_redirection(cmd, cmd_str))
		return (0);
	return (1);
}

int	init_table(char *line, char **env, t_command_table *table)
{
	char		**cmd_strs;
	int			pipe_fd[2];
	size_t		i;

	cmd_strs = ft_split(line, '|');
	if (!cmd_strs)
		return (0);
	table->n_commands = 0;
	while (cmd_strs[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return (0);
	i = 0;
	while (i < table->n_commands)
	{
		// if (i < table->n_commands - 1)
		// 	pipe(pipe_fd);
		if (!init_cmd(&table->commands[i], cmd_strs[i], env))
			return (0);

		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_command_table	table;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[0mminishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		if (init_table(line, env, &table))
			run_pipeline(table);
		free(line);
	}
	return (0);
}
