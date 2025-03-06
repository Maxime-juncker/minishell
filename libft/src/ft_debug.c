/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:51:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 09:39:48 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	debug_color(const char *msg, const char *color)
{
	ft_printf("%s%s\033[0m\n", color, msg);
}

void	warning(const char *msg)
{
	debug_color(msg, YELLOW);
}

void	alert(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s\033[0m\n", B_RED, msg);
}

void	error(const char *msg)
{
	debug_color(msg, RED);
}

int	malloc_assert(void *mem, const char *file, int line, const char *function)
{
	if (mem)
		return (0);
	ft_dprintf(2, "%s%s:%d: %sminishell: malloc assertion failed in %s'%s'\n",
		GRAY, file, line, RED, RESET, function);
	return (-1);
}
