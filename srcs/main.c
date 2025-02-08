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
		add_history(line);
		if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
			return (printf("exit\n"), 0);
		process_cmd = process_line(line);
		code = check_cmd(process_cmd);
		if (code == SYNTAX_ERR || code == IS_DIR)
			continue ;
		else if (code == MALLOC_ERR)
			exit(EXIT_FAILURE); //! need to cleanup if needed
		if (process_cmd && !ft_strncmp(process_cmd, "\n", ft_strlen(process_cmd)))
			new_prompt(0);
		last_cmd = init_table(process_cmd, env, &table, last_cmd);
		if (last_cmd != 127)
			last_cmd = run_pipeline(&table);
		free(line);
		free(process_cmd);
	}
	return (0);
}
