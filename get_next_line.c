/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:20 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/18 21:03:54 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
char	*process_read(int fd, char **rest_buffer)
{
	char	*buffer;
	int		read_result;
	char	*next_line;
	char	*dup;
	char	*joined;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (*rest_buffer)
			ft_free(rest_buffer);
		return (NULL);
	}
	while (1)
	{
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result < 0)
		{
			if (*rest_buffer)
				ft_free(rest_buffer);
			return (free(buffer), NULL);
		}
		buffer[read_result] = '\0';
		if (read_result == 0)
		{
			if (*rest_buffer && *rest_buffer[0] != '\0')
			{
				next_line = ft_strdup(*rest_buffer);
				if (!next_line)
					return (free(buffer), ft_free(rest_buffer), NULL);
			}
			else
				next_line = NULL;
			return (free(buffer), ft_free(rest_buffer), next_line);
		}
		if (is_string_contain_character(buffer, '\n'))
		{
			next_line = line_before_character(buffer, '\n');
			if (!next_line)
				return (free(buffer), ft_free(rest_buffer), NULL);
			if (!*rest_buffer)
			{
				dup = ft_strdup(ft_strchr(buffer, '\n'));
				if (!dup)
					return (free(next_line), free(buffer), NULL);
				return (*rest_buffer = dup, free(buffer), next_line);
			}
			joined = ft_strjoin(*rest_buffer, next_line);
			if (!joined)
				return (free(next_line), free(buffer), ft_free(rest_buffer),
					NULL);
			free(next_line);
			dup = ft_strdup(ft_strchr(buffer, '\n'));
			if (!dup)
				return (free(joined), free(buffer), ft_free(rest_buffer), NULL);
			return (free(*rest_buffer), *rest_buffer = dup, free(buffer),
				joined);
		}
		if (*rest_buffer)
		{
			joined = ft_strjoin(*rest_buffer, buffer);
			if (!joined)
				return (free(buffer), ft_free(rest_buffer), NULL);
			free(*rest_buffer);
			*rest_buffer = joined;
		}
		else
		{
			*rest_buffer = ft_strdup(buffer);
			if (!*rest_buffer)
				return (free(buffer), NULL);
		}
		free(buffer);
		if (read_result < BUFFER_SIZE)
			return (next_line = *rest_buffer, *rest_buffer = NULL, next_line);
	}
}

char	*get_next_line(int fd)
{
	static char	*rest_buffer;
	char		*next_line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (is_string_contain_character(rest_buffer, '\n'))
	{
		next_line = line_before_character(rest_buffer, '\n');
		if (!next_line)
			return (ft_free(&rest_buffer), NULL);
		temp = ft_strdup(ft_strchr(rest_buffer, '\n'));
		if (!temp)
			return (free(next_line), ft_free(&rest_buffer), NULL);
		return (free(rest_buffer), rest_buffer = temp, next_line);
	}
	return (process_read(fd, &rest_buffer));
}

/**
 * @brief returns string before character included character
 *
 * @param str
 * @param c
 * @return char*
 * @warning FREE
 */
char	*line_before_character(char *str, int c)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			result = malloc(i + 2);
			if (!result)
				return (NULL);
			ft_strlcpy(result, str, i + 2);
			return (result);
		}
		i++;
	}
	if (str[i] == (char)c)
		return (ft_strdup(str));
	return (NULL);
}

bool	is_string_contain_character(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (true);
		i++;
	}
	if (str[i] == (char)c)
		return (true);
	return (false);
}
