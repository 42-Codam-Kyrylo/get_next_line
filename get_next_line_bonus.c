/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:20 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/19 19:56:33 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	*rest_buffer[FD_SETSIZE];
	char		*next_line;
	char		*temp;

	if (fd < 0 || fd >= FD_SETSIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(rest_buffer[fd], '\n'))
	{
		next_line = line_before_character(rest_buffer[fd], '\n');
		if (!next_line)
			return (free(rest_buffer[fd]), rest_buffer[fd] = NULL, NULL);
		temp = ft_strdup(ft_strchr(rest_buffer[fd], '\n'));
		if (!temp)
			return (free(next_line), free(rest_buffer[fd]),
				rest_buffer[fd] = NULL, NULL);
		return (free(rest_buffer[fd]), rest_buffer[fd] = temp, next_line);
	}
	return (process_read(fd, &rest_buffer[fd]));
}

char	*handle_buffer_new_line(char **next_line, char **buffer,
		char **rest_buffer)
{
	char	*joined;
	char	*dup;

	*next_line = line_before_character(*buffer, '\n');
	if (!*next_line)
		return (free(*buffer), free(*rest_buffer), *rest_buffer = NULL, NULL);
	if (!*rest_buffer)
	{
		dup = ft_strdup(ft_strchr(*buffer, '\n'));
		if (!dup)
			return (free(*next_line), free(*buffer), NULL);
		return (*rest_buffer = dup, free(*buffer), *next_line);
	}
	joined = ft_strjoin(*rest_buffer, *next_line);
	if (!joined)
		return (free(*next_line), free(*buffer), free(*rest_buffer),
			*rest_buffer = NULL, NULL);
	free(*next_line);
	dup = ft_strdup(ft_strchr(*buffer, '\n'));
	if (!dup)
		return (free(joined), free(*buffer), free(*rest_buffer),
			*rest_buffer = NULL, NULL);
	return (free(*rest_buffer), *rest_buffer = dup, free(*buffer), joined);
}

char	*handle_read_result0(char **rest_buffer, char **next_line,
		char **buffer)
{
	if (*rest_buffer && *rest_buffer[0] != '\0')
	{
		*next_line = ft_strdup(*rest_buffer);
		if (!*next_line)
			return (free(*buffer), free(*rest_buffer), *rest_buffer = NULL,
				NULL);
	}
	else
		*next_line = NULL;
	return (free(*buffer), free(*rest_buffer), *rest_buffer = NULL, *next_line);
}

char	*handle_no_line_buffer(char **rest_buffer, char **buffer,
		int read_result, int fd)
{
	char	*joined;
	char	*next_line;

	if (*rest_buffer)
	{
		joined = ft_strjoin(*rest_buffer, *buffer);
		if (!joined)
			return (free(*buffer), free(*rest_buffer), *rest_buffer = NULL,
				NULL);
		free(*rest_buffer);
		*rest_buffer = joined;
	}
	else
	{
		*rest_buffer = ft_strdup(*buffer);
		if (!*rest_buffer)
			return (free(*buffer), NULL);
	}
	free(*buffer);
	if (read_result < BUFFER_SIZE)
		return (next_line = *rest_buffer, *rest_buffer = NULL, next_line);
	return (get_next_line(fd));
}

char	*process_read(int fd, char **rest_buffer)
{
	char	*buffer;
	int		read_result;
	char	*next_line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (*rest_buffer)
			ft_free(rest_buffer);
		return (NULL);
	}
	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result < 0)
	{
		if (*rest_buffer)
			ft_free(rest_buffer);
		return (free(buffer), NULL);
	}
	buffer[read_result] = '\0';
	if (read_result == 0)
		return (handle_read_result0(rest_buffer, &next_line, &buffer));
	if (!ft_strchr(buffer, '\n'))
		return (handle_no_line_buffer(rest_buffer, &buffer, read_result, fd));
	return (handle_buffer_new_line(&next_line, &buffer, rest_buffer));
}
