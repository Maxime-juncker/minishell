/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:37:27 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/20 16:33:45 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_up(void)
{
	char	*path;
	char	*tmp;
	int		lenght;
	char	buffer[1024];

	path = getcwd(buffer, sizeof(buffer));
	if (!path)
		return (NULL);
	tmp = ft_strrchr(path, '/');
	if (tmp == NULL)
		return (ft_strdup("/"));
	lenght = tmp - path;
	if (lenght == 0)
		return (ft_strdup("/"));
	tmp = ft_substr(path, 0, lenght);
	return (tmp);
}

char	*get_pwd(int *is_malloc_error)
{
	char	buffer[1024];
	char	*res;

	if (!getcwd(buffer, sizeof(buffer)))
	{
		ft_printf("%spwd: error retrieving current directory: getcwd:%s%s", RED,
			" cannot access parent directories: No such file or directory\n",
			RESET);
		return (NULL);
	}
	res = ft_strdup(buffer);
	if (malloc_assert(res, __FILE__, __LINE__, __FUNCTION__))
		*is_malloc_error = 1;
	return (res);
}

int	pwd(const t_command *cmd)
{
	char	*path;
	int		is_malloc_error;

	if (cmd->n_args > 1 && !(cmd->args[1][0] != '-'
		|| !cmd->args[1][1] || (cmd->args[1][1] == '-' && !cmd->args[1][2])))
	{
		ft_dprintf(2, "%sminishell: pwd: -%c: invalid option\n%s%s",
			RED, cmd->args[1][1], "pwd: usage: pwd\n", RESET);
		return (2);
	}
	is_malloc_error = 0;
	path = get_pwd(&is_malloc_error);
	if (is_malloc_error)
		return (MALLOC_ERR);
	else if (!path)
		return (1);
	ft_printf("%s\n", path);
	free(path);
	return (0);
}
