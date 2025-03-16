/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:06:14 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 15:44:27 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_process_cmd(t_command_table *table, char *line, int *code,
		t_list **to_free)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split_operators(line);
	free(line);
	if (!args)
		return (MALLOC_ERR);
	if (ft_lstadd_back(to_free, ft_lstnew(args)) == -1)
		return (ft_lstclear(to_free, cleanup_pacakge), MALLOC_ERR);
	while (args[i])
	{
		if ((args[i][0] == '(' || (ft_strcmp(args[i], "&&")
				&& ft_strcmp(args[i], "||"))) && MALLOC_ERR ==
				handle_line_symbol(table, args[i++], code, to_free))
			return (MALLOC_ERR);
		if (!args[i])
			break ;
		if ((*code == 0 && !ft_strcmp(args[i], "&&"))
			|| (*code != 0 && !ft_strcmp(args[i], "||")))
			i++;
		else if (args[i + 1])
			i += 2;
	}
	return (*code);
}

static int	exec_prompt(t_command_table *table, char *line)
{
	t_list	*lst;
	int		res;

	lst = NULL;
	if (check_cmd_line(process_line(line, table->env, &table->code),
			&table->code) != 0)
		return (0);
	res = handle_process_cmd(table, line, &table->code, &lst);
	ft_lstclear(&lst, cleanup_pacakge);
	return (res);
}

int	load_config(t_command_table *table)
{
	int		fd;
	char	*path;
	char	*line;

	path = find_env_var(table->env, "HOME", NULL);
	if (path == NULL)
		return (0);
	path = ft_strjoin_free(path, "/.minishellrc", FREE1);
	if (malloc_assert(path, __FILE__, __LINE__, __FUNCTION__))
		return (0);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (0);
	table->setup_fd = fd;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		exec_prompt(table, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (table->code);
}