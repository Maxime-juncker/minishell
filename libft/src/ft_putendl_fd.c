/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:20:48 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/19 15:30:45 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return (0);
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
	return (ft_strlen(s) + 1);
}
