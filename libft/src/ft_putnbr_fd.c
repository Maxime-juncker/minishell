/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:26:23 by mjuncker          #+#    #+#             */
/*   Updated: 2024/11/20 08:57:51 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	*nb;
	int		len;

	nb = ft_itoa(n);
	len = ft_strlen(nb);
	while (len > 0)
	{
		ft_putchar_fd(nb[ft_strlen(nb) - len], fd);
		len--;
	}
	len = ft_strlen(nb);
	free(nb);
	return (len);
}

int	ft_putnbr_hex(unsigned long int nbr, char *base, int fd)
{
	char	buffer[16];
	int		i;
	int		count;

	if (nbr == 0)
		return (ft_putchar_fd('0', fd));
	i = 0;
	count = 0;
	while (nbr > 0)
	{
		buffer[i++] = base[nbr % 16];
		nbr /= 16;
	}
	while (i > 0)
	{
		ft_putchar_fd(buffer[--i], fd);
		count++;
	}
	return (count);
}

int	ft_putaddr(long int nbr, char *base, int fd)
{
	ft_putstr_fd("0x", 1);
	return (ft_putnbr_hex(nbr, base, fd) + 2);
}
