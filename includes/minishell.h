/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:55:59 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 16:21:14 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------------------------------------------------- */
/*                                   includes                                 */
/* -------------------------------------------------------------------------- */

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                   defines                                  */
/* -------------------------------------------------------------------------- */

# define IGNORE			-2
# define MALLOC_ERR		-1
# define SYNTAX_ERR		2
# define NOT_FOUND		127
# define PERM_DENIED	126
# define IS_DIR			126

# define DEBUG 0
# define SHOW_LEXER 0

/* -------------------------------------------------------------------------- */
/*                                command table                               */
/* -------------------------------------------------------------------------- */

typedef struct s_command
{
	char	**args;
	size_t	n_args;
	int		pid;

	int		fd_in;
	int		fd_out;
	char	**env;
	int		code;
}	t_command;

typedef struct s_command_table
{
	char		*name;
	t_command	*commands;
	size_t		n_commands;

	char		**env;
	char		**exp;

	int			setup_fd;
	int			code;
}	t_command_table;

typedef struct s_free_package
{
	int		*childs;
	t_list	*args;
}	t_free_pkg;

extern int	g_signal_received;

/* -------------------------------------------------------------------------- */
/*                                   prompt/                                  */
/* -------------------------------------------------------------------------- */

// prompt_line.c
char	*new_prompt_txt(char **env);

// prompt.c
int		handle_line_symbol(t_command_table *table, char *arg, int *code,
			t_list **to_free);

/* -------------------------------------------------------------------------- */
/*                                   builtin                                  */
/* -------------------------------------------------------------------------- */

// cd.c
int		cd_command(const t_command_table *table, const t_command cmd);
char	*find_env_var(char **env, char *to_find, int *index);

// echo.c
int		echo(char **args, int n);

// env.c
int		env(t_command_table table, const t_command cmd);
char	**duplicate_env(char **old_env);
size_t	arrlen(void **arr);

// export_utils.c
int		export_env(t_command_table *table, char *arg, int append);
int		malloc_assert(void *mem, const char *file,
			int line, const char *function);

// export.c
int		export_cmd(t_command_table *table, t_command cmd);
void	sort_export(char **argv);

// pwd.c
int		pwd(const t_command cmd);

// unset.c
int		unset_cmd(t_command_table *table, t_command cmd);
int		unset_if_needed(t_command_table *table, char *arg);
int		get_env_len(char **env, char *arg);

// exit.c
void	exit_shell(t_command_table *table, t_command cmd, t_free_pkg package);

/* -------------------------------------------------------------------------- */
/*                                   checker                                  */
/* -------------------------------------------------------------------------- */

// checker_utils.c
int		in_base(const char c, const char *base);
int		token_error(char c1, char c2);
void	cleanup_arr(void **arr);
void	cleanup_pacakge(void *package);

// checker.c
int		check_cmd_line(char *process_line, int *code);

// path_checker.c
int		check_path(const char *cmd_part, char **env);

// redir_checker.c
int		check_redir_in(const char *cmd_line, int i);
int		new_line_error(const char *str, const char last);
char	*remove_quotes_pair(char *s);

// split_line.c
t_list	*split_line(char *line);

// syntax_checker.c
int		check_syntax(const char *cmd_line);

// token_error.c
int		check_token_error(const char *cmd_line, int i, int max_occ,
			char to_find);
int		check_quotes(const char *cmd_line);

int		check_and_op(const char *line, int i);

// parenthesis_checker.c
int		check_parenthesis(const char *line);

// pipe_checker.c
int		check_pipe(const char *line, int index);

/* -------------------------------------------------------------------------- */
/*                                   executor                                 */
/* -------------------------------------------------------------------------- */

// cmd_debug.c
void	show_table(t_command_table table);
void	show_cmd(t_command cmd);

// executor.c
int		run_command(t_command *cmd, const t_command_table *table,
			t_free_pkg package);

// pipeline_utils.c
void	close_fds(t_command cmd);
void	close_all_fds(const t_command_table *table);
void	cleanup_child(const t_command_table *table);

// paths.c
char	*get_cmd_path(char **paths, t_command cmd);
int		is_builtin(char *name);
char	**get_paths(char **env);

// pipeline.c
int		run_pipeline(t_command_table *table, t_list *args);

// builtin_cmd.c
int		env_stage(t_command_table *table, t_command cmd, int *code,
			t_free_pkg package);
int		run_built_in(const t_command cmd, const t_command_table *table);

// waiter.c
int		wait_for_process(t_command_table *table, int *childs, int *code);

/* -------------------------------------------------------------------------- */
/*                                    lexer                                   */
/* -------------------------------------------------------------------------- */

// join_lst.c
char	*join_lst(t_list *lst);
int		ignore_prompt(char *prompt);

// lexer_utils.c
char	toggle_quote(char c, char quote);
int		is_symbol(char c);

// lexer.c
char	*process_line(const char *cmd_line, char **env, int *code);

// quote_utils.c
size_t	get_str_len(const char *str);

// var_processing.c
t_list	*process_expanded_vars(const t_list *lst, char **env, int last_code);
char	*process_var(char *str, char **env, int last_code, t_list *next);

t_list	*process_quotes(const char *line);
char	*remove_spaces(char *str);

// wildcard_processing.c
char	*process_wildcard(char *line);

// wildcard_expansion.c
char	*expand_wildcard(char *line);

// wildcard_patern.c
char	**new_patern(char *line);
int		patern_valid(char *tmp, char **patern, int *i);

// wildcard_utils.c
size_t	count_files(char *path);

/* -------------------------------------------------------------------------- */
/*                                   parser                                   */
/* -------------------------------------------------------------------------- */

// init.c
int		init_table(char *line, t_command_table *table);

// redir.c
int		redir(t_command *cmd);

// ft_split_pipe.c
char	**ft_split_pipe(const char *s);

/* -------------------------------------------------------------------------- */
/*                                   others                                   */
/* -------------------------------------------------------------------------- */

// utils.c
void	init_env(t_command_table *table, char **env);
void	cleanup_table(t_command_table *table);
void	handle_signal(int signal);
int		check_interrupt(void);

// prompt.c
int		new_prompt(t_command_table *table);

char	**ft_split_operators(const char *s);
void	free_all(char **res, int i);

char	*get_exec_name(char *name);

// config.c
int		load_config(t_command_table *table);

#endif
