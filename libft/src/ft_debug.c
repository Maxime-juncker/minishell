/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:51:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/13 12:43:40 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// colors
#define RESET	"\033[0m"
#define BLACK	"\033[0;30m"
#define RED		"\033[0;31m"
#define GREEN	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define BLUE	"\033[0;34m"
#define PURPLE	"\033[0;35m"
#define CYAN	"\033[0;36m"
#define WHITE	"\033[0;37m"
#define GRAY	"\033[0;30m"

// Background
#define B_BLACK		"\033[40m"
#define B_RED		"\033[41m"
#define B_GREEN		"\033[42m"
#define B_YELLOW	"\033[43m"
#define B_BLUE		"\033[44m"
#define B_PURPLE	"\033[45m"
#define B_CYAN		"\033[46m"
#define B_WHITE		"\033[47m"

void	debug_color(const char *msg, const char *color)
{
	ft_printf("%s%s\033[0m\n", color, msg);
}

void	success(const char *msg)
{
	debug_color(msg, GREEN);
}

void	warning(const char *msg)
{
	debug_color(msg, YELLOW);
}

void	alert(const char *msg)
{
	debug_color(msg, B_RED);
}

void	error(const char *msg)
{
	debug_color(msg, RED);
}
