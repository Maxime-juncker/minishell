#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>

char	*remove_special_characters(char *line)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	char	*clean_line;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	clean_line = malloc(ft_strlen(line) + 1);
	if (!clean_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (line[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote && (line[i] == '\\' || line[i] == ';'))
			i++;
		else
			clean_line[j++] = line[i++];
	}
	return (clean_line[j] = 0, clean_line);
}

int	check_unclosed_quotes(char *line, char *quote)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (line[i] == '\'' && double_quotes % 2 == 0)
			single_quotes = !single_quotes;
		else if (line[i] == '\"' && single_quotes % 2 == 0)
			double_quotes = !double_quotes;
		i++;
	}
	if (single_quotes && quote)
		*quote = '\'';
	else if (double_quotes && quote)
		*quote = '\"';
	return (single_quotes || double_quotes);
}

char	*read_with_quotes(char *line)
{
	char	*new_line;
	char	*prompt;
	int		unclosed_quotes;
	char	quote;

	quote = ' ';
	unclosed_quotes = check_unclosed_quotes(line, &quote);
	while (unclosed_quotes)
	{
		if (quote == '\"')
			prompt = "dquote> ";
		else
			prompt = "quote> ";
		new_line = readline(prompt);
		if (!new_line)
			return (NULL);
		line = ft_strjoin(line, new_line);
		free(new_line);
		unclosed_quotes = check_unclosed_quotes(line, NULL);
	}
	return (line);
}

char	*expand_variable(char *str, char **env)
{
	char	*expanded_str;
	char	*env_var;
	char	*env_value;
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	var_len;
	size_t	var_start;
	char	*tmp_expanded_str;

	expanded_str = malloc(1);
	if (!expanded_str)
		return (NULL);
	expanded_str[0] = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			i++;
			var_start = i;
			while (str[i] && (str[i] != ' ' && str[i] != '$' && str[i] != '"' && str[i] != '\''))
				i++;
			var_len = i - var_start;
			env_var = ft_strdup(&str[var_start]);
			env_value = getenv(env_var);
			free(env_var);
			tmp_expanded_str = expanded_str;
			if (env_value)
				expanded_str = ft_strjoin(expanded_str, env_value);
			else
				expanded_str = ft_strjoin(expanded_str, &str[var_start]);
			free(tmp_expanded_str);
		}
		else
		{
			tmp_expanded_str = expanded_str;
			expanded_str = ft_strjoin(expanded_str, (char[]){str[i], '\0'});
			free(tmp_expanded_str);
			i++;
		}
	}
	return (expanded_str);
}



int	init_table(char *line, char **env, t_command_table *table)
{
	t_command	cmd;
	int			pipefd[2];
	char		**commands;
	int			i;
	int			j;
	int			fd;
	char		*delimiter;
	char		*heredoc_input;
	int			heredoc_fd;

	line = read_with_quotes(line);
	if (!line)
		return (0);
	line = remove_special_characters(line);
	commands = ft_split(line, '|');
	if (!commands)
		return (0);
	table->n_commands = 0;
	while (commands[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return (0);
	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].args = ft_split(commands[i], ' ');
		if (!table->commands[i].args)
			return (0);
		table->commands[i].n_args = 0;
		while (table->commands[i].args[table->commands[i].n_args])
			table->commands[i].n_args++;
		j = 0;
		while (j < table->commands[i].n_args)
		{
			char *expanded_arg = expand_variable(table->commands[i].args[j], env);
			free(table->commands[i].args[j]);
			table->commands[i].args[j] = expanded_arg;
			j++;
		}
		table->commands[i].path = get_cmd_path(get_paths(env), table->commands[i]);
		if (!table->commands[i].path)
			return (0);
		if (i < table->n_commands - 1 && pipe(pipefd) == -1)
			return (0);
		if (i == 0)
			table->commands[i].fd_in = STDIN_FILENO;
		else
			table->commands[i].fd_in = pipefd[0];
		if (i == table->n_commands - 1)
			table->commands[i].fd_out = STDOUT_FILENO;
		else
			table->commands[i].fd_out = pipefd[1];
		j = 0;
		while (j < table->commands[i].n_args)
		{
			if (table->commands[i].args[j][0] == '<')
			{
				table->commands[i].fd_in = open(table->commands[i].args[j + 1], O_RDONLY);
				if (table->commands[i].fd_in == -1)
					return (0);
				j++;
			}
			else if (table->commands[i].args[j][0] == '>')
			{
				if (table->commands[i].args[j][1] == '>')
				{
					fd = open(table->commands[i].args[j + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
					if (fd == -1)
						return (0);
					table->commands[i].fd_out = fd;
					j++;
				}
				else
				{
					fd = open(table->commands[i].args[j + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
					if (fd == -1)
						return (0);
					table->commands[i].fd_out = fd;
					j++;
				}
			}
			else if (table->commands[i].args[j][0] == '<' && table->commands[i].args[j][1] == '<')
			{
				delimiter = table->commands[i].args[j + 1];
				heredoc_input = NULL;
				heredoc_fd = open("/tmp/heredoc_temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
				if (heredoc_fd == -1)
					return (0);
				while (1)
				{
					heredoc_input = readline("> ");
					if (!heredoc_input)
						return (0);
					if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter)) == 0)
					{
						free(heredoc_input);
						break;
					}
					write(heredoc_fd, heredoc_input, ft_strlen(heredoc_input));
					write(heredoc_fd, "\n", 1);
					free(heredoc_input);
				}
				close(heredoc_fd);
				table->commands[i].fd_in = open("/tmp/heredoc_temp.txt", O_RDONLY);
				j++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	print_table(t_command_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->n_commands)
	{
		j = 0;
		while (j < table->commands[i].n_args)
		{
			printf("%s ", table->commands[i].args[j]);
			j++;
		}
		printf("\n");
		i++;
	}
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
