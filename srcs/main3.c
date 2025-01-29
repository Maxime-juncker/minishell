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
		else if (in_single_quote || (in_double_quote && line[i] != '$'))
			clean_line[j++] = line[i++];
		else
			i++;
	}
	clean_line[j] = 0;
	return (clean_line);
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

void	handle_heredoc(t_command_table *table, int i, int j)
{
	char	*delimiter;
	char	*input_line;
	char	*here_doc_input;
	int		len;

	delimiter = table->commands[i].args[j + 1];
	here_doc_input = malloc(1);
	len = 0;
	if (!here_doc_input)
		return ;
	while (1)
	{
		input_line = readline("heredoc> ");
		if (!input_line || ft_strncmp(input_line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(input_line);
			break ;
		}
		here_doc_input = realloc(here_doc_input, len + ft_strlen(input_line) + 2);
		strcpy(here_doc_input + len, input_line);
		len += ft_strlen(input_line);
		here_doc_input[len++] = '\n';
		free(input_line);
	}
	table->commands[i].fd_in = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(table->commands[i].fd_in, here_doc_input, len);
	close(table->commands[i].fd_in);
	table->commands[i].fd_in = open("/tmp/heredoc.tmp", O_RDONLY);
	free(here_doc_input);
}

void	init_table(char *line, char **env, t_command_table *table)
{
	t_command	cmd;
	int			pipefd[2];
	char		**commands;
	int			i;
	int			j;
	int			fd;

	line = read_with_quotes(line);
	if (!line)
		return ;
	line = remove_special_characters(line);
	commands = ft_split(line, '|');
	if (!commands)
		return ;
	table->n_commands = 0;
	while (commands[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return ;
	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].args = ft_split(commands[i], ' ');
		if (!table->commands[i].args)
			return ;
		table->commands[i].n_args = 0;
		while (table->commands[i].args[table->commands[i].n_args])
			table->commands[i].n_args++;
		table->commands[i].path = get_cmd_path(get_paths(env), table->commands[i]);
		if (i < table->n_commands - 1 && pipe(pipefd) == -1)
			return ;
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
					return ;
				j++;
			}
			else if (table->commands[i].args[j][0] == '>')
			{
				if (table->commands[i].args[j][1] == '>')
				{
					fd = open(table->commands[i].args[j + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
					if (fd == -1)
						return ;
					table->commands[i].fd_out = fd;
					j++;
				}
				else
				{
					fd = open(table->commands[i].args[j + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
					if (fd == -1)
						return ;
					table->commands[i].fd_out = fd;
					j++;
				}
			}
			else if (ft_strncmp(table->commands[i].args[j], "<<", 3) == 0)
			{
				handle_heredoc(table, i, j);
				j++;
			}
			j++;
		}
		i++;
	}
}


// void	print_table(t_command_table *table)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < table->n_commands)
// 	{
// 		j = 0;
// 		while (j < table->commands[i].n_args)
// 		{
// 			printf("%s ", table->commands[i].args[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_command_table	table;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		init_table(line, env, &table);
		// print_table(&table);
		free(line);
	}
	return (0);
}
