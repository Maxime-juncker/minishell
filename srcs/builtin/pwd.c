/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:37:27 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/26 14:20:09 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd(int *is_malloc_error)
{
	char	buffer[1024];
	char	*res;

	if (!getcwd(buffer, sizeof(buffer)))
	{
		printf("%spwd: error retrieving current directory: getcwd:%s%s", RED,
			" cannot access parent directories: No such file or directory\n",
			RESET);
		return (NULL);
	}
	res = ft_strdup(buffer);
	if (!res)
	{
		malloc_assert(ERR);
		*is_malloc_error = 1;
	}
	return (res);
}

int	pwd(void)
{
	char	*path;
	int		is_malloc_error;

	is_malloc_error = 0;
	path = get_pwd(&is_malloc_error);
	if (is_malloc_error)
		return (MALLOC_ERR);
	else if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}
