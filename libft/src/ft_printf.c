/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:15:36 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/19 12:15:59 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_next_stop(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

static int	handle_characters(const char *type, va_list *ptr)
{
	void	*tmp;

	if (*type == 'c')
		return (ft_putchar_fd(va_arg(*ptr, int) % 256, 1));
	else if (*type == 's')
	{
		tmp = va_arg(*ptr, char *);
		if (tmp == NULL)
			return (ft_putstr_fd("(null)", 1));
		return (ft_putstr_fd(tmp, 1));
	}
	else if (*type == 'p')
	{
		tmp = va_arg(*ptr, void *);
		if (tmp == NULL)
			return (ft_putstr_fd("(nil)", 1));
		return (ft_putaddr((long int)tmp, "0123456789abcdef", 1));
	}
	else if (*type == '%')
		return (ft_putchar_fd('%', 1));
	else
		return (ft_printf("%%%c", *type));
	return (0);
}

static int	handle_stop(const char *type, va_list *ptr)
{
	void	*tmp;
	int		len;

	type++;
	if (*type == 'd' || *type == 'i')
		return (ft_putnbr_fd(va_arg(*ptr, int), 1));
	else if (*type == 'u')
	{
		tmp = (char *)ft_uitoa(va_arg(*ptr, unsigned int));
		ft_putstr_fd(tmp, 1);
		len = ft_strlen(tmp);
		free(tmp);
		return (len);
	}
	else if (*type == 'x' || *type == 'X')
	{
		if (*type == 'x')
			return (ft_putnbr_hex(va_arg(*ptr, unsigned int),
					"0123456789abcdef", 1));
		else
			return (ft_putnbr_hex(va_arg(*ptr, unsigned int),
					"0123456789ABCDEF", 1));
	}
	return (handle_characters(type, ptr));
}

int	ft_printf(const char *s, ...)
{
	size_t			nb_write;
	va_list			ptr;
	char			*block;

	if (s == NULL)
		return (-1);
	nb_write = 0;
	va_start(ptr, s);
	while (*s)
	{
		block = ft_substr(s, 0, get_next_stop(s));
		nb_write += ft_putstr_fd(block, 1);
		s += ft_strlen(block);
		if (block)
			free(block);
		if (*s != '%' || (*s == '%' && s[1] == '\0'))
			return (nb_write);
		nb_write += handle_stop(s, &ptr);
		s += 2;
	}
	return (nb_write);
}
