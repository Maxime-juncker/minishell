#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>

void pipex(char **args, char **env)
{
	(void)args;
	t_cmd cmd;

	cmd.args = ft_split("ls -l", ' ');
	cmd.n_args = 2;
	exec_cmd(get_path(env), cmd);

	// int fd[2]; // fd[1] == write | fd[0] == read

	// if (pipe(fd) == -1)
	// {
	// 	perror("\033[31mError");
	// 	return ;
	// }

	// int pid1 = fork();
	// if (pid1 == -1)
	// {
	// 	return ;
	// }

	// if (pid1 == 0) // child process
	// {
	// 	int	infile = open(args[1], O_RDONLY);
	// 	if (infile == -1)
	// 	{
	// 		perror("\033[31mError");
	// 		return ;
	// 	}
	// 	dup2(infile, STDIN_FILENO);
	// 	close(infile);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	exec_cmd(get_path(env), args[2]);
	// }

	// int pid2 = fork();
	// if (pid2 == -1)
	// 	return ;

	// if (pid2 == 0)
	// {
	// 	int	outfile = open(args[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// 	if (outfile == -1)
	// 	{
	// 		perror("\033[31mError");
	// 		return ;
	// 	}
	// 	// child
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	dup2(outfile, STDOUT_FILENO);

	// 	exec_cmd(get_path(env), args[3]);
	// }

	// close(fd[0]);
	// close(fd[1]);

	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
}