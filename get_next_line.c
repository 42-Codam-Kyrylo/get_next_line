/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:20 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/17 16:43:28 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

char	*get_next_line(int fd)
{
	if(fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	static char *rest_buffer;
	char *buffer;
	char *next_line;

	bool is_next_line_rb = is_string_contain_character(rest_buffer, '\n');
	if(is_next_line_rb) {
		next_line = line_before_character(rest_buffer, '\n');
		if (!next_line) {
			free(rest_buffer);
			rest_buffer = NULL;
			return NULL;
		}
		char *temp = ft_strdup(ft_strchr(rest_buffer, '\n'));
		if (!temp) {
			free(next_line);
			free(rest_buffer);
			rest_buffer = NULL;
			return NULL;
		}
		free(rest_buffer);
		rest_buffer = temp;
		return next_line;
	}

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer) {
		if (rest_buffer) {
			free(rest_buffer);
			rest_buffer = NULL;
		}
		return NULL;
	}
	
	int read_result = read(fd, buffer, BUFFER_SIZE);
	
	if(read_result < 0) {
		free(buffer);
		if (rest_buffer) {
			free(rest_buffer);
			rest_buffer = NULL;
		}
		return NULL;
	}

	buffer[read_result] = '\0';

	if(read_result == 0) {
		if(rest_buffer && rest_buffer[0] != '\0') {
			next_line = ft_strdup(rest_buffer);
			if(!next_line) {
				free(buffer);
				free(rest_buffer);
				rest_buffer = NULL;
				return NULL;
			}
		} else {
			next_line = NULL;
		}
		free(buffer);
		free(rest_buffer);
		rest_buffer = NULL;
		return next_line;
	}

	bool is_next_line_in_buffer = is_string_contain_character(buffer, '\n');
	if (!is_next_line_in_buffer) {
		
		if (rest_buffer) {
			char *temp = ft_strjoin(rest_buffer, buffer);
			if(!temp) {
				free(buffer);
				free(rest_buffer);
				rest_buffer = NULL;
				return NULL;
			}
			free(rest_buffer);
			rest_buffer = temp;
		} else {
			rest_buffer = ft_strdup(buffer);
			if (!rest_buffer) {
				free(buffer);
				return NULL;
			}
		}
		free(buffer);

		if (!rest_buffer)
			return NULL;

		if(read_result < BUFFER_SIZE) {
			next_line = rest_buffer;
			rest_buffer = NULL;
			return next_line;
		}
			
		return get_next_line(fd);
	}

	next_line = line_before_character(buffer, '\n');
	if (!next_line) {
		free(buffer);
		free(rest_buffer);
		rest_buffer = NULL;
		return NULL;
	}
	
	if(!rest_buffer) {
		char *dup = ft_strdup(ft_strchr(buffer, '\n'));
		if (!dup) {
			free(next_line);
			free(buffer);
			return NULL;
		}
		rest_buffer = dup;
		free(buffer);
		return next_line;
	}

	char *old_next_line = next_line;
	char *joined = ft_strjoin(rest_buffer, next_line);
	if (!joined) {
		free(old_next_line);
		free(buffer);
		free(rest_buffer);
		rest_buffer = NULL;
		return NULL;
	}
	free(old_next_line);
	char *dup = ft_strdup(ft_strchr(buffer, '\n'));
	if (!dup) {
		free(joined);
		free(buffer);
		free(rest_buffer);
		rest_buffer = NULL;
		return NULL;
	}
	free(rest_buffer);
	rest_buffer = dup;
	free(buffer);
	return joined;
}
/**
 * @brief returns string before character included character
 * 
 * @param str 
 * @param c 
 * @return char* 
 * @warning dont forget to free
 */
char *line_before_character(char *str, int c) {
	int	i;

	if(!str)
		return NULL;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			char *result = malloc(i + 2);
			if(!result)
				return NULL;
			ft_strlcpy(result, str, i + 2);
			return result;
		}
		i++;
	}
	if (str[i] == (char)c)
		return ft_strdup(str);
	return (NULL);
}

bool is_string_contain_character(char *str, int c) {
	int i = 0;

	if(!str)
		return false;

	while(str[i]) {
		if (str[i] == (char)c)
			return true;
		i++;
	}
	if (str[i] == (char)c)
		return (true);
	return false;
}

