/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:17 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/21 15:07:24 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_line( const char *process_line, char **env )
{
	int		code;
	char	**cmd_parts;
	int		i;
	int		tmp;

	if (!process_line || ft_strcmp((char*)process_line, ":") == 0 || ft_strcmp((char*)process_line, "!") == 0)
		return (0);
	code = check_syntax(process_line);
	if (code != 0)
		return (code);
	cmd_parts = ft_split(process_line, '|');
	if (cmd_parts == NULL)
		return (MALLOC_ERR);
	i = 0;
	code = 0;
	while (cmd_parts[i])
	{
		tmp = check_path(cmd_parts[i], env);
		if (tmp != 0)
			code = tmp;
		i++;
	}
	cleanup_arr((void **)cmd_parts);
	return (code);
}
