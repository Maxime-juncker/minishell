/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:23:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/05 12:07:16 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	full_dump(char *buffer, char **line)
{
	char	*new;

	new = ft_strjoin(*line, buffer);
	if (new == NULL)
	{
		if (*line != NULL)
			free(*line);
		return (-1);
	}
	if (*line != NULL)
		free(*line);
	*line = new;
	ft_bzero(buffer, ft_strlen(buffer));
	return (0);
}

static int	dump_buffer(char *buffer, char **line)
{
	char	*new;
	int		len;

	new = 0x0;
	if (buffer[0])
	{
		if (ft_strchr(buffer, '\n') != NULL)
		{
			len = ft_strlen(*line) + ft_strchr(buffer, '\n') - buffer + 2;
			new = ft_calloc(len, sizeof(char));
			if (new == NULL)
				return (-1);
			if (*line)
				ft_strlcpy(new, *line, len);
			ft_strlcat(new, buffer, len);
			ft_memmove(buffer, buffer + (ft_strchr(buffer, '\n') - buffer + 1),
				BUFFER_SIZE);
			if (*line)
				free(*line);
			*line = new;
			return (1);
		}
		return (full_dump(buffer, line));
	}
	return (1);
}

static int	read_line(int fd, char *buffer, char **line)
{
	int	nb_read;

	nb_read = read(fd, buffer, BUFFER_SIZE);
	if (nb_read == -1)
	{
		if (*line != NULL)
			free(*line);
		return (-1);
	}
	return (nb_read);
}

/*
 * @brief get next line will return the next line of the given file
 * @brief or null if an error occure of the file is already read
 * @param fd the file descriptor to read the file
 * @return the next line or null
 * @note the user is responsible for managing the return value
*/
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	int			nb_read;
	int			code;

	line = 0x0;
	nb_read = 0;
	if (fd < 0)
		return (NULL);
	if (dump_buffer(buffer, &line) == -1)
		return (NULL);
	while (nb_read != -1)
	{
		nb_read = read_line(fd, buffer, &line);
		if (nb_read == -1)
			return (NULL);
		if (nb_read == 0)
			return (line);
		code = dump_buffer(buffer, &line);
		if (code == -1)
			return (NULL);
		if (code == 1 || nb_read != BUFFER_SIZE)
			return (line);
	}
	return (NULL);
}
