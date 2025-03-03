/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:16:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/03 12:46:10 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_to_endl(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	while (s2[i] && s2[i] != '\n')
		i++;
	if (!s2[i])
		i--;
	j = 0;
	if (s1)
		while (s1[j])
			j++;
	res = malloc(i + j + 2);
	if (!res)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			res[i++] = *s1++;
	while (*s2 && *s2 != '\n')
		res[i++] = *s2++;
	if (*s2 == '\n')
		res[i++] = '\n';
	return (res[i] = '\0', res);
}

static void	update_buffer(char buffer[BUFFER_SIZE + 1])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	while (buffer[j])
		buffer[j++] = 0;
}

static char	*extract_line(int fd, char buffer[BUFFER_SIZE + 1], char *res)
{
	int		read_output;
	char	*temp;
	int		i;

	while (!ft_strchr(buffer, '\n'))
	{
		i = 0;
		while (buffer[i])
			buffer[i++] = 0;
		read_output = read(fd, buffer, BUFFER_SIZE);
		if (read_output < 0)
			return (free(res), NULL);
		else if (read_output == 0)
			break ;
		temp = ft_strjoin_to_endl(res, buffer);
		free(res);
		if (!temp)
			return (NULL);
		res = temp;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buffer[FD][BUFFER_SIZE + 1];
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD)
		return (NULL);
	res = NULL;
	if (buffer[fd][0])
	{
		res = ft_strjoin_to_endl(res, buffer[fd]);
		if (!res)
			return (NULL);
	}
	res = extract_line(fd, buffer[fd], res);
	if (!res)
		return (NULL);
	update_buffer(buffer[fd]);
	return (res);
}
