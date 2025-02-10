#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	new_prompt(int sig)
{
	if (sig)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_command_table	table;
	int				last_cmd;
	int				code;
	char			*process_cmd;

	(void)ac;
	(void)av;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	table.env = env;
	last_cmd = 0;
	while (1)
	{
		line = readline("\033[0mminishell$ ");
		if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
			return (printf("exit\n"), 0);
		else if (ft_strncmp(line, "\n", ft_strlen(line)))
			add_history(line);
		if (ft_strncmp(line, "\n", ft_strlen(line)) && ft_strncmp(line, "!", ft_strlen(line)) && ft_strncmp(line, ":", ft_strlen(line)))
		{
			process_cmd = process_line(line);
			code = check_cmd_line(process_cmd);
			if (code == SYNTAX_ERR || code == IS_DIR)
				break ;
			else if (code == MALLOC_ERR)
				exit(EXIT_FAILURE); //! need to cleanup if needed
			last_cmd = init_table(process_cmd, env, &table, last_cmd);
			free(process_cmd);
			if (last_cmd != 127)
				last_cmd = run_pipeline(&table);
		}
		free(line);
	}
	return (0);
}

