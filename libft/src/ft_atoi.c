/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:28:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/13 12:52:53 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long n, int sign)
{
	if (n * 10 / 10 != n)
	{
		if (sign < 0)
			return (0);
		return (-1);
	}
	return (2);
}

static int	get_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	while (s[*i] == ' ' || (s[*i] >= '\t' && s[*i] <= '\r'))
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	n = 0;
	sign = get_sign(nptr, &i);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (check_overflow(n, sign) != 2)
			return (check_overflow(n, sign));
		n *= 10;
		n += nptr[i] - '0';
		i++;
	}
	n *= sign;
	return ((int)n);
}

static int	call_func(int n, void (*f)(int, void *), void *param)
{
	if (n < 0)
		warning("underflow atoi");
	else
		warning("overflow atoi");
	if (f == NULL)
		return (n);
	f(n, param);
	return (n);
}

/*
 * @brief overflow_check will run like ft_atoi, however in case of an
 * @brief overflow, a f will be call with the MAX_INT (overflow) or
 * @brief MIN_INT (underflow) along with a void* param
 * @param s the string to convert
 * @param f the function to call in case an overflow or underflow happen
 * @param param the param to pass to f
 * @return the converted int, or MAX_INT / MIN_INT (overflow / underflow)
*/
int	overflow_check(const char *s, void (*f)(int, void *), void *param)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = get_sign(s, &i);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (result > MAX_INT / 10)
			return (call_func(MAX_INT, f, param));
		if (result < MIN_INT / 10)
			return (call_func(MIN_INT, f, param));
		result *= 10;
		if (result > MAX_INT - (s[i] - '0'))
			return (call_func(MAX_INT, f, param));
		if (result < MIN_INT + (s[i] - '0'))
			return (call_func(MIN_INT, f, param));
		if (sign < 0)
			result -= s[i] - '0';
		else
			result += s[i] - '0';
		i++;
	}
	return (result);
}
